//
// Copyright (c) 2019-2023 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BHO_MYSQL_DETAIL_EXECUTION_PROCESSOR_EXECUTION_STATE_IMPL_HPP
#define BHO_MYSQL_DETAIL_EXECUTION_PROCESSOR_EXECUTION_STATE_IMPL_HPP

#include <asio2/bho/mysql/diagnostics.hpp>
#include <asio2/bho/mysql/error_code.hpp>
#include <asio2/bho/mysql/field_view.hpp>
#include <asio2/bho/mysql/metadata.hpp>
#include <asio2/bho/mysql/metadata_collection_view.hpp>
#include <asio2/bho/mysql/string_view.hpp>

#include <asio2/bho/mysql/detail/config.hpp>
#include <asio2/bho/mysql/detail/execution_processor/execution_processor.hpp>

#include <asio2/bho/assert.hpp>

#include <vector>

namespace bho {
namespace mysql {
namespace detail {

class execution_state_impl final : public execution_processor
{
    struct ok_data
    {
        bool has_value{false};           // The OK packet information is default constructed, or actual data?
        std::uint64_t affected_rows{};   // OK packet data
        std::uint64_t last_insert_id{};  // OK packet data
        std::uint16_t warnings{};        // OK packet data
        bool is_out_params{false};       // Does this resultset contain OUT param information?
    };

    std::vector<metadata> meta_;
    ok_data eof_data_;
    std::vector<char> info_;

    void on_new_resultset() noexcept
    {
        meta_.clear();
        eof_data_ = ok_data{};
        info_.clear();
    }

    BHO_MYSQL_DECL
    void on_ok_packet_impl(const ok_view& pack);

    BHO_MYSQL_DECL
    void reset_impl() noexcept override final;

    BHO_MYSQL_DECL
    error_code on_head_ok_packet_impl(const ok_view& pack, diagnostics&) override final;

    BHO_MYSQL_DECL
    void on_num_meta_impl(std::size_t num_columns) override final;

    BHO_MYSQL_DECL
    error_code on_meta_impl(const coldef_view&, bool, diagnostics&) override final;

    BHO_MYSQL_DECL
    error_code on_row_impl(span<const std::uint8_t> msg, const output_ref&, std::vector<field_view>& fields)
        override final;

    BHO_MYSQL_DECL
    error_code on_row_ok_packet_impl(const ok_view& pack) override final;

    void on_row_batch_start_impl() noexcept override final {}

    void on_row_batch_finish_impl() noexcept override final {}

public:
    execution_state_impl() = default;

    metadata_collection_view meta() const noexcept { return meta_; }

    std::uint64_t get_affected_rows() const noexcept
    {
        BHO_ASSERT(eof_data_.has_value);
        return eof_data_.affected_rows;
    }

    std::uint64_t get_last_insert_id() const noexcept
    {
        BHO_ASSERT(eof_data_.has_value);
        return eof_data_.last_insert_id;
    }

    unsigned get_warning_count() const noexcept
    {
        BHO_ASSERT(eof_data_.has_value);
        return eof_data_.warnings;
    }

    string_view get_info() const noexcept
    {
        BHO_ASSERT(eof_data_.has_value);
        return string_view(info_.data(), info_.size());
    }

    bool get_is_out_params() const noexcept
    {
        BHO_ASSERT(eof_data_.has_value);
        return eof_data_.is_out_params;
    }

    execution_state_impl& get_interface() noexcept { return *this; }
};

}  // namespace detail
}  // namespace mysql
}  // namespace bho

#ifdef BHO_MYSQL_HEADER_ONLY
#include <asio2/bho/mysql/impl/execution_state_impl.ipp>
#endif

#endif
