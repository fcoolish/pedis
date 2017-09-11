// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// Decodes the blocks generated by block_builder.cc.
//
// Modified by Pedis 

#include "store/table/block.hh"
#include "utils/managed_bytes.hh"
#include <vector>
#include <algorithm>
//#include "store/table/format.hh"
//#include "store/util/coding.hh"

namespace store {

inline uint32_t block::num_restarts() const {
  // mock
  return 0;
  //assert(_size >= sizeof(uint32_t));
  //return DecodeFixed32(data_ + size_ - sizeof(uint32_t));
}

block::block(managed_bytes cache_key, const managed_bytes data)
    : _lru_link()
    , _cache_link()
    : _key(std::move(cached_key))
    , _data(std::move(data))
    , _size(static_cast<uint32_t>(_data.size()))
{
  if (_size < sizeof(uint32_t)) {
    _size = 0;  // Error marker
  } else {
    size_t max_restarts_allowed = (_size - sizeof(uint32_t)) / sizeof(uint32_t);
    if (num_restarts() > max_restarts_allowed) {
      // The size is too small for NumRestarts()
      _size = 0;
    } else {
      _restart_offset = _size - (1 + num_restarts()) * sizeof(uint32_t);
    }
  }
}

block::~block() {
}

}
