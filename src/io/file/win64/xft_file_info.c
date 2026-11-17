/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

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
	const t_u64a	epoch = 116444736000000000;
	FILE_BASIC_INFO	basic;
	bool			w;
	bool			x;

	if (!GetFileInformationByHandleEx(file, FileBasicInfo,
			&basic, sizeof(basic)))
		return (false);
	info->acc_time = ((t_u64a)basic.LastAccessTime.QuadPart - epoch) * 100;
	info->mod_time = ((t_u64a)basic.LastWriteTime.QuadPart - epoch) * 100;
	info->chg_time = ((t_u64a)basic.ChangeTime.QuadPart - epoch) * 100;
	info->bth_time = ((t_u64a)basic.CreationTime.QuadPart - epoch) * 100;
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

__attribute__((__nonnull__(2)))
t_result	xft_fileinfo_from_fd(t_fd fd, t_file_info *fileinfo)
{
	const HANDLE	file = (HANDLE)fd;
	bool			ok;

	*fileinfo = (t_file_info){.type = xft__file_type(file, 0)};
	if (__builtin_expect(fileinfo->type == F_T_UNKNOWN, 0))
		return (KO);
	if (fileinfo->type != F_T_DISK)
		return (OK);
	ok = xft__times(file, fileinfo) && xft__sizes(file, fileinfo);
	return ((t_result)ok);
}

__attribute__((__nonnull__(1, 2)))
t_result	xft_fileinfo_from_name(const char *name, t_file_info *fileinfo)
{
	const DWORD	share = FILE_SHARE_READ | FILE_SHARE_WRITE
		| FILE_SHARE_DELETE;
	const DWORD	flags = FILE_FLAG_BACKUP_SEMANTICS
		| FILE_FLAG_OPEN_REPARSE_POINT;
	HANDLE		file;
	t_result	ok;

	file = CreateFileA(name, FILE_READ_ATTRIBUTES, share, nullptr,
			OPEN_EXISTING, flags, nullptr);
	if (__builtin_expect(file == INVALID_HANDLE_VALUE, 0))
		return (KO);
	ok = xft_fileinfo_from_fd((t_fd)file, fileinfo);
	CloseHandle(file);
	return (ok);
}

#endif
