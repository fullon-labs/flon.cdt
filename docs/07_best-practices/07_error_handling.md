---
content_title: Error handling
---

Contracts can use `uint64_t` error codes as an alternative (and shorter) means of signaling error conditions, as opposed to string error messages. However, FullOn and CDT reserve certain ranges of the `uint64_t` value space for their own purposes. Contract developers must be aware of the following ranges and restrictions:

1. $0 - 4,999,999,999,999,999,999$:  
Available for contract developers to assign error codes specific to their contracts.

2. $5,000,000,000,000,000,000 - 7,999,999,999,999,999,999$:  
Reserved for the CDT compiler to allocate as appropriate. Although the WASM code generated by the CDT compiler may use error code values that were automatically generated from within this range, the error codes in this range are meant to have meaning specific to the particular compiled contract (the meaning would typically be conveyed through the mapping between the error code value and strings in the associated generated ABI file).

3. $8,000,000,000,000,000,000 - 9,999,999,999,999,999,999$:  
Reserved for the CDT compiler to allocate as appropriate. The error codes in this range are not specific to any contract but rather are used to convey general runtime error conditions associated with the generated code by CDT.

4. $10,000,000,000,000,000,000 - 18,446,744,073,709,551,615$:  
Reserved by the FullOn protocol to represent protocol-level error conditions. FullOn will actually enforce this by restricting the ability for `eosio_assert_code` to be used to fail with error code values used within this range.

Therefore, contract developers should only reserve error codes from the first range above to use in their contracts.
