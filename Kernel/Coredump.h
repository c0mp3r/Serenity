/*
 * Copyright (c) 2019-2020, Jesse Buhagiar <jooster669@gmail.com>
 * Copyright (c) 2020, Itamar S. <itamar8910@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/OwnPtr.h>
#include <Kernel/Forward.h>
#include <Kernel/Library/NonnullLockRefPtr.h>

namespace Kernel {

class Coredump {
public:
    static ErrorOr<NonnullOwnPtr<Coredump>> try_create(NonnullLockRefPtr<Process>, StringView output_path);

    ~Coredump() = default;
    ErrorOr<void> write();

private:
    Coredump(NonnullLockRefPtr<Process>, NonnullLockRefPtr<OpenFileDescription>);
    static ErrorOr<NonnullLockRefPtr<OpenFileDescription>> try_create_target_file(Process const&, StringView output_path);

    ErrorOr<void> write_elf_header();
    ErrorOr<void> write_program_headers(size_t notes_size);
    ErrorOr<void> write_regions();
    ErrorOr<void> write_notes_segment(ReadonlyBytes);

    ErrorOr<void> create_notes_segment_data(auto&) const;
    ErrorOr<void> create_notes_process_data(auto&) const;
    ErrorOr<void> create_notes_threads_data(auto&) const;
    ErrorOr<void> create_notes_regions_data(auto&) const;
    ErrorOr<void> create_notes_metadata_data(auto&) const;

    NonnullLockRefPtr<Process> m_process;
    NonnullLockRefPtr<OpenFileDescription> m_description;
    size_t m_num_program_headers { 0 };
};

}
