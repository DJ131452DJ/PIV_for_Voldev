/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2014-2023 Riccardo Ostani - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BITITEMSVECTOR_HPP
#define BITITEMSVECTOR_HPP

#include <map>
#include <memory>

#include "bitabstractarchivehandler.hpp"
#include "bitfs.hpp"
#include "bittypes.hpp"

namespace bit7z {

using std::vector;
using std::map;
using std::unique_ptr;

namespace filesystem {
class FSItem;
} // namespace filesystem

using filesystem::FSItem;

struct GenericInputItem;
using GenericInputItemPtr = std::unique_ptr< GenericInputItem >;
using GenericInputItemVector = std::vector< GenericInputItemPtr >;

/** @cond **/
struct IndexingOptions {
    bool recursive = true;
    bool retain_folder_structure = false;
    bool only_files = false;
    bool follow_symlinks = true;
};
/** @endcond **/

/**
 * @brief The BitItemsVector class represents a vector of generic input items, i.e., items that can come
 * from the filesystem, from memory buffers, or from standard streams.
 */
class BitItemsVector final {
    public:
        using value_type = GenericInputItemPtr;

        BitItemsVector() = default;

        BitItemsVector( const BitItemsVector& ) = default;

        BitItemsVector( BitItemsVector&& ) = default;

        auto operator=( const BitItemsVector& ) -> BitItemsVector& = default;

        auto operator=( BitItemsVector&& ) -> BitItemsVector& = default;

        /**
         * @brief Indexes the given directory, adding to the vector all the files that match the wildcard filter.
         *
         * @param in_dir    the directory to be indexed.
         * @param filter    (optional) the wildcard filter to be used for indexing;
         *                  empty string means "index all files".
         * @param policy    (optional) the filtering policy to be applied to the matched items.
         * @param options   (optional) the settings to be used while indexing the given directory
         *                  and all of its subdirectories.
         */
        void indexDirectory( const fs::path& in_dir,
                             const tstring& filter = {},
                             FilterPolicy policy = FilterPolicy::Include,
                             IndexingOptions options = {} );

        /**
         * @brief Indexes the given vector of filesystem paths, adding to the item vector all the files.
         *
         * @param in_paths  the vector of filesystem paths.
         * @param options   (optional) the settings to be used while indexing the given directory
         *                  and all of its subdirectories.
         */
        void indexPaths( const std::vector< tstring >& in_paths, IndexingOptions options = {} );

        /**
         * @brief Indexes the given map of filesystem paths, adding to the vector all the files.
         *
         * @note Map keys represent the filesystem paths to be indexed; the corresponding mapped values are
         * the user-defined (possibly different) paths wanted inside archives.
         *
         * @param in_paths  map of filesystem paths with the corresponding user-defined path desired inside the
         *                  output archive.
         * @param options   (optional) the settings to be used while indexing the given directory
         *                  and all of its subdirectories.
         */
        void indexPathsMap( const std::map< tstring, tstring >& in_paths, IndexingOptions options = {} );

        /**
         * @brief Indexes the given file path, with an optional user-defined path to be used in output archives.
         *
         * @note If a directory path is given, a BitException is thrown.
         *
         * @param in_file         the path to the filesystem file to be indexed in the vector.
         * @param name            (optional) user-defined path to be used inside archives.
         * @param follow_symlinks (optional) whether to follow symbolic links or not.
         */
        void indexFile( const tstring& in_file, const tstring& name = {}, bool follow_symlinks = true );

        /**
         * @brief Indexes the given buffer, using the given name as a path when compressed in archives.
         *
         * @param in_buffer the buffer containing the file to be indexed in the vector.
         * @param name      user-defined path to be used inside archives.
         */
        void indexBuffer( const std::vector< byte_t >& in_buffer, const tstring& name );

        /**
         * @brief Indexes the given standard input stream, using the given name as a path when compressed in archives.
         *
         * @param in_stream the standard input stream of the file to be indexed in the vector.
         * @param name      user-defined path to be used inside archives.
         */
        void indexStream( std::istream& in_stream, const tstring& name );

        /**
         * @return the size of the items vector.
         */
        BIT7Z_NODISCARD auto size() const -> std::size_t;

        /**
         * @param index the index of the desired item in the vector.
         * @return a constant reference to the GenericInputItem at the given index.
         */
        auto operator[]( GenericInputItemVector::size_type index ) const -> const GenericInputItem&;

        /**
         * @return an iterator to the first element of the vector; if the vector is empty,
         *         the returned iterator will be equal to the end() iterator.
         */
        BIT7Z_NODISCARD auto begin() const noexcept -> GenericInputItemVector::const_iterator;

        /**
         * @return an iterator to the element following the last element of the vector;
         *         this element acts as a placeholder: attempting to access it results in undefined behavior.
         */
        BIT7Z_NODISCARD auto end() const noexcept -> GenericInputItemVector::const_iterator;

        /**
         * @return an iterator to the first element of the vector; if the vector is empty,
         *         the returned iterator will be equal to the end() iterator.
         */
        BIT7Z_NODISCARD auto cbegin() const noexcept -> GenericInputItemVector::const_iterator;

        /**
         * @return an iterator to the element following the last element of the vector;
         *         this element acts as a placeholder: attempting to access it results in undefined behavior.
         */
        BIT7Z_NODISCARD auto cend() const noexcept -> GenericInputItemVector::const_iterator;

        ~BitItemsVector();

    private:
        GenericInputItemVector mItems;

        void indexItem( const FSItem& item, IndexingOptions options );
};

}  // namespace bit7z

#endif //BITITEMSVECTOR_HPP
