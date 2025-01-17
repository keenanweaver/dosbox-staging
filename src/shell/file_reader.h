/*
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *
 *  Copyright (C) 2023-2023  The DOSBox Staging Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef DOSBOX_FILE_READER_H
#define DOSBOX_FILE_READER_H

#include <optional>
#include <string>

#include "shell.h"

class FileReader final : public ByteReader {
public:
	static std::optional<FileReader> GetFileReader(const std::string& file);

	void Reset() final;
	std::optional<uint8_t> Read() final;

	~FileReader() final;

	FileReader(const FileReader&)            = delete;
	FileReader& operator=(const FileReader&) = delete;

	FileReader(FileReader&& other) noexcept;
	FileReader& operator=(FileReader&& other) noexcept;

private:
	explicit FileReader(uint16_t file_handle);
	std::optional<uint16_t> handle;
};

#endif
