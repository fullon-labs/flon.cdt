#pragma once
#include "producer_schedule.hpp"
#include "system.hpp"
#include "../../core/eosio/crypto.hpp"
#include "../../core/eosio/name.hpp"
#include "../../core/eosio/serialize.hpp"

namespace eosio {

   namespace internal_use_do_not_use {
      extern "C" {
         __attribute__((eosio_wasm_import))
         bool is_privileged( uint64_t account );

         __attribute__((eosio_wasm_import))
         void get_resource_limits( uint64_t account, uint64_t* gas, bool* is_unlimited );

         __attribute__((eosio_wasm_import))
         void set_resource_limits( uint64_t account, uint64_t gas, bool is_unlimited );

         __attribute__((eosio_wasm_import))
         void set_privileged( uint64_t account, bool is_priv );

         __attribute__((eosio_wasm_import))
         void set_blockchain_parameters_packed( char* data, uint32_t datalen );

         __attribute__((eosio_wasm_import))
         uint32_t get_blockchain_parameters_packed( char* data, uint32_t datalen );

         __attribute((eosio_wasm_import))
         int64_t set_proposed_producers( char*, uint32_t );

         __attribute__((eosio_wasm_import))
         void preactivate_feature( const capi_checksum256* feature_digest );

         __attribute__((eosio_wasm_import))
         int64_t set_proposed_producers_ex( uint64_t producer_data_format, char *producer_data, uint32_t producer_data_size );
      }
   }

  /**
   *  @defgroup privileged Privileged
   *  @ingroup contracts
   *  @brief Defines C++ Privileged API
   */

   /**
    *  Tunable blockchain configuration that can be changed via consensus
    *  @ingroup privileged
    */
   struct blockchain_parameters {

      /**
      * The maximum net usage in instructions for a block
      * @brief the maximum net usage in instructions for a block
      */
      uint64_t max_block_net_usage;

      /**
      * The target percent (1% == 100, 100%= 10,000) of maximum net usage; exceeding this triggers congestion handling
      * @brief The target percent (1% == 100, 100%= 10,000) of maximum net usage; exceeding this triggers congestion handling
      */
      uint32_t target_block_net_usage_pct;

      /**
      * The maximum objectively measured net usage that the chain will allow regardless of account limits
      * @brief The maximum objectively measured net usage that the chain will allow regardless of account limits
      */
      uint32_t max_transaction_net_usage;

      /**
       * The base amount of net usage billed for a transaction to cover incidentals
       */
      uint32_t base_per_transaction_net_usage;

      /**
       * The amount of net usage leeway available whilst executing a transaction (still checks against new limits without leeway at the end of the transaction)
       * @brief The amount of net usage leeway available whilst executing a transaction  (still checks against new limits without leeway at the end of the transaction)
       */
      uint32_t net_usage_leeway;

      /**
      * The numerator for the discount on net usage of context-free data
      * @brief The numerator for the discount on net usage of context-free data
      */
      uint32_t context_free_discount_net_usage_num;

      /**
      * The denominator for the discount on net usage of context-free data
      * @brief The denominator for the discount on net usage of context-free data
      */
      uint32_t context_free_discount_net_usage_den;

      /**
      * The maximum billable cpu usage (in microseconds) for a block
      * @brief The maximum billable cpu usage (in microseconds) for a block
      */
      uint32_t max_block_cpu_usage;

      /**
      * The target percent (1% == 100, 100%= 10,000) of maximum cpu usage; exceeding this triggers congestion handling
      * @brief The target percent (1% == 100, 100%= 10,000) of maximum cpu usage; exceeding this triggers congestion handling
      */
      uint32_t target_block_cpu_usage_pct;

      /**
      * The maximum billable cpu usage (in microseconds) that the chain will allow regardless of account limits
      * @brief The maximum billable cpu usage (in microseconds) that the chain will allow regardless of account limits
      */
      uint32_t max_transaction_cpu_usage;

      /**
      * The minimum billable cpu usage (in microseconds) that the chain requires
      * @brief The minimum billable cpu usage (in microseconds) that the chain requires
      */
      uint32_t min_transaction_cpu_usage;

      /**
       * Maximum lifetime of a transaction
       * @brief Maximum lifetime of a transaction
       */
      uint32_t max_transaction_lifetime;

      /**
      * The number of seconds after the time a deferred transaction can first execute until it expires
      * @brief the number of seconds after the time a deferred transaction can first execute until it expires
      */
      uint32_t deferred_trx_expiration_window;


      /**
      * The maximum number of seconds that can be imposed as a delay requirement by authorization checks
      * @brief The maximum number of seconds that can be imposed as a delay requirement by authorization checks
      */
      uint32_t max_transaction_delay;

      /**
       * Maximum size of inline action
       * @brief Maximum size of inline action
       */
      uint32_t max_inline_action_size;

      /**
       * Maximum depth of inline action
       * @brief Maximum depth of inline action
       */
      uint16_t max_inline_action_depth;

      /**
       * Maximum authority depth
       * @brief Maximum authority depth
       */
      uint16_t max_authority_depth;

      /**
       * Maximum total ram usage in bytes.
       * @brief Maximum total ram usage in bytes.
       */
      ///<
      uint64_t   max_total_ram_usage;

      /**
       * Gas per cpu millisecond
       * @brief Gas per cpu millisecond
       */
      uint32_t   gas_per_cpu_ms;
      /**
       * Gas per net kilobyte
       * @brief Gas per net kilobyte
       */
      uint32_t   gas_per_net_kb;
      /**
       * Gas per ram per kilobyte
       * @brief Gas per ram per kilobyte
       */
      uint32_t   gas_per_ram_kb;

      EOSLIB_SERIALIZE( blockchain_parameters,
                        (max_block_net_usage)(target_block_net_usage_pct)
                        (max_transaction_net_usage)(base_per_transaction_net_usage)(net_usage_leeway)
                        (context_free_discount_net_usage_num)(context_free_discount_net_usage_den)

                        (max_block_cpu_usage)(target_block_cpu_usage_pct)
                        (max_transaction_cpu_usage)(min_transaction_cpu_usage)

                        (max_transaction_lifetime)(deferred_trx_expiration_window)(max_transaction_delay)
                        (max_inline_action_size)(max_inline_action_depth)(max_authority_depth)
                        (max_total_ram_usage)(gas_per_cpu_ms)(gas_per_net_kb)(gas_per_ram_kb)
      )
   };

   /**
    *  Set the blockchain parameters
    *
    *  @ingroup privileged
    *  @param params - New blockchain parameters to set
    */
   void set_blockchain_parameters(const eosio::blockchain_parameters& params);

   /**
    *  Retrieve the blolckchain parameters
    *
    *  @ingroup privileged
    *  @param params - It will be replaced with the retrieved blockchain params
    */
   void get_blockchain_parameters(eosio::blockchain_parameters& params);

    /**
    *  Get the resource limits of an account
    *
    *  @ingroup privileged
    *  @param account - name of the account whose resource limit to get
    *  @param ram_bytes -  output to hold retrieved ram limit in absolute bytes
    *  @param net_weight - output to hold net limit
    *  @param cpu_weight - output to hold cpu limit
    */
   inline void get_resource_limits( name account, uint64_t& gas, bool& is_unlimited ) {
      internal_use_do_not_use::get_resource_limits( account.value, &gas, &is_unlimited );
   }

   /**
    * Set the resource limits of an account.
    *
    * @ingroup privileged
    *
    * @param account - name of the account whose resource limit to be set.
    * @param gas - available gas limit.
    * @param is_unlimited - Whether the account has unlimited resources.
   */
   inline void set_resource_limits( name account, uint64_t gas, bool is_unlimited ) {
      internal_use_do_not_use::set_resource_limits( account.value, gas, is_unlimited );
   }

   /**
    *  Proposes a schedule change using the legacy producer key format
    *
    *  @ingroup privileged
    *  @note Once the block that contains the proposal becomes irreversible, the schedule is promoted to "pending" automatically. Once the block that promotes the schedule is irreversible, the schedule will become "active"
    *  @param producers - vector of producer keys
    *
    *  @return an optional value of the version of the new proposed schedule if successful
    */
   std::optional<uint64_t> set_proposed_producers( const std::vector<producer_key>& prods );

   /**
    *  Proposes a schedule change using the more flexible key format
    *
    *  @ingroup privileged
    *  @note Once the block that contains the proposal becomes irreversible, the schedule is promoted to "pending" automatically. Once the block that promotes the schedule is irreversible, the schedule will become "active"
    *  @param producers - vector of producer authorities
    *
    *  @return an optional value of the version of the new proposed schedule if successful
    */
   inline std::optional<uint64_t> set_proposed_producers( const std::vector<producer_authority>& prods ) {
      auto packed_prods = eosio::pack( prods );
      int64_t ret = internal_use_do_not_use::set_proposed_producers_ex(1, (char*)packed_prods.data(), packed_prods.size());
      if (ret >= 0)
        return static_cast<uint64_t>(ret);
      return {};
   }

   /**
    *  Check if an account is privileged
    *
    *  @ingroup privileged
    *  @param account - name of the account to be checked
    *  @return true if the account is privileged
    *  @return false if the account is not privileged
    */
   inline bool is_privileged( name account ) {
      return internal_use_do_not_use::is_privileged( account.value );
   }

   /**
    *  Set the privileged status of an account
    *
    *  @ingroup privileged
    *  @param account - name of the account whose privileged account to be set
    *  @param is_priv - privileged status
    */
   inline void set_privileged( name account, bool is_priv ) {
      internal_use_do_not_use::set_privileged( account.value, is_priv );
   }

   /**
    * Pre-activate protocol feature
    *
    * @ingroup privileged
    * @param feature_digest - digest of the protocol feature to pre-activate
    */
   inline void preactivate_feature( const checksum256& feature_digest ) {
      auto feature_digest_data = feature_digest.extract_as_byte_array();
      internal_use_do_not_use::preactivate_feature(
         reinterpret_cast<const internal_use_do_not_use::capi_checksum256*>( feature_digest_data.data() )
      );
   }

}
