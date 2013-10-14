suffer-db is a key-value database that has exactly three operations:

* `ADD <key> <value>`: Associate `<value>` with `<key>`.
* `DEL <key> [value]`: Unassociate `[value]` with `<key>`, unassociating all values if `[value]` is omitted.
* `GET <subkey>`: Get all keys and their values that contain `<subkey>` as a substring of the key.


This git repository contains submodules. Please clone with `git clone --recursive`.


Build requirements:

* [scons](http://www.scons.org/)
* A C11 compliant compiler, like [clang](http://clang.llvm.org/)
* [libevent](http://libevent.org/)
