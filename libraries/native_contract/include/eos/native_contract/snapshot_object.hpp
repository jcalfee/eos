/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <string>
#include <eos/chain/types.hpp>
#include <eos/chain/multi_index_includes.hpp>

#include <eos/types/types.hpp>

#include <chainbase/chainbase.hpp>

namespace native {
namespace eos {
namespace chain = ::eos::chain;
namespace types = ::eos::types;
namespace config = ::eos::config;

using std::string;

/**
 * @brief The SnapshotObject class tracks the EOS balance for accounts
 */
class SnapshotObject : public chainbase::object<chain::snapshot_object_type, SnapshotObject> {
   OBJECT_CTOR(SnapshotObject)

   id_type id;
   types::PublicKey eosKey;
   string ethAddress;
   types::Asset balance = 0;
};

struct byEosKey;
struct byEthAddress;

using SnapshotMultiIndex = chainbase::shared_multi_index_container<
   SnapshotObject,
   indexed_by<
      ordered_unique<tag<by_id>,
         member<SnapshotObject, SnapshotObject::id_type, &SnapshotObject::id>
      >,
      ordered_unique<tag<byEosKey>,
         member<SnapshotObject, types::PublicKey, &SnapshotObject::eosKey>
      >,
      ordered_unique<tag<byEthAddress>,
         member<SnapshotObject, string, &SnapshotObject::ethAddress>
      >
   >
>;

} } // namespace native::eos

CHAINBASE_SET_INDEX_TYPE(native::eos::SnapshotObject, native::eos::SnapshotMultiIndex)
