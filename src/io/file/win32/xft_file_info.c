/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 22:42:26 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 23:02:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/files.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __const__))
static inline t_u64a	xft__nanos(LARGE_INTEGER time)
{
	return (((t_u64a)time.QuadPart - 116444736000000000) * 100);
}

__attribute__((__always_inline__))
static inline t_file_type	xft__file_type(HANDLE file, DWORD attrs)
{
	FILE_ATTRIBUTE_TAG_INFO	tag;
	DWORD					type;

	if (attrs & FILE_ATTRIBUTE_REPARSE_POINT)
	{
		if (!GetFileInformationByHandleEx(file, FileAttributeTagInfo,
				&tag, sizeof(tag)))
			return (F_T_UNKNOWN);
		if (IsReparseTagNameSurrogate(tag.ReparseTag))
			return (F_T_SYML);
		if (tag.ReparseTag == IO_REPARSE_TAG_AF_UNIX)
			return (F_T_SOCK);
	}
	if (attrs & FILE_ATTRIBUTE_DIRECTORY)
		return (F_T_DIR);
	type = GetFileType(file);
	if (type == FILE_TYPE_DISK)
		return (F_T_DISK);
	if (type == FILE_TYPE_CHAR)
		return (F_T_DEV);
	if (type == FILE_TYPE_PIPE)
		return (F_T_PIPE);
	return (F_T_UNKNOWN);
}

__attribute__((__always_inline__, __nonnull__(2)))
static inline bool	xft__times(HANDLE file, t_file_info *__restrict__ info)
{
	FILE_BASIC_INFO	basic;
	bool			w;
	bool			x;

	if (!GetFileInformationByHandleEx(file, FileBasicInfo,
			&basic, sizeof(basic)))
		return (false);
	info->acc_time = xft__nanos(basic.LastAccessTime);
	info->mod_time = xft__nanos(basic.LastWriteTime);
	info->chg_time = xft__nanos(basic.ChangeTime);
	info->bth_time = xft__nanos(basic.CreationTime);
	w = !(basic.FileAttributes & FILE_ATTRIBUTE_READONLY);
	x = !!(basic.FileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	info->perms = (t_file_perms){
		.o_exec = x, .o_write = w, .o_read = 1,
		.g_exec = x, .g_write = w, .g_read = 1,
		.u_exec = x, .u_write = w, .u_read = 1,
	};
	info->type = xft__file_type(file, basic.FileAttributes);
	return (true);
}

// n_blks counts 512 byte blocks like st_blocks
__attribute__((__always_inline__, __nonnull__(2)))
static inline bool	xft__sizes(HANDLE file, t_file_info *__restrict__ info)
{
	BY_HANDLE_FILE_INFORMATION	ids;
	FILE_STANDARD_INFO			std;
	FILE_STORAGE_INFO			storage;

	if (!GetFileInformationByHandle(file, &ids)
		|| !GetFileInformationByHandleEx(file, FileStandardInfo,
			&std, sizeof(std))
		|| !GetFileInformationByHandleEx(file, FileStorageInfo,
			&storage, sizeof(storage)))
		return (false);
	info->size = (t_u64a)std.EndOfFile.QuadPart;
	info->blk_size = storage.PhysicalBytesPerSectorForPerformance;
	info->n_blks = (t_u64a)std.AllocationSize.QuadPart / 512;
	info->inode = (t_u64a)ids.nFileIndexHigh << 32 | ids.nFileIndexLow;
	info->dev_id = ids.dwVolumeSerialNumber;
	info->lnk_cnt = ids.nNumberOfLinks;
	return (true);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_file_info	xft_file_info(t_blk8r path)
{
	HANDLE		file;
	t_file_info	info;
	bool		ok;

	file = CreateFileA((LPCSTR)path, FILE_READ_ATTRIBUTES,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
			OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS
			| FILE_FLAG_OPEN_REPARSE_POINT, nullptr);
	if (__builtin_expect(file == INVALID_HANDLE_VALUE, 0))
		return ((t_file_info){.type = F_T_UNKNOWN});
	info = (t_file_info){0};
	ok = xft__times(file, &info) && xft__sizes(file, &info);
	CloseHandle(file);
	if (__builtin_expect(!ok, 0))
		return ((t_file_info){.type = F_T_UNKNOWN});
	return (info);
}

#endif
