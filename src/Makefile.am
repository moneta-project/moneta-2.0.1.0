DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

MONETA_CONFIG_INCLUDES=-I$(builddir)/config
MONETA_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

MONETA_INCLUDES += -I$(srcdir)/secp256k1/include

LIBMONETA_SERVER=libmoneta_server.a
LIBMONETA_WALLET=libmoneta_wallet.a
LIBMONETA_COMMON=libmoneta_common.a
LIBMONETA_CLI=libmoneta_cli.a
LIBMONETA_UTIL=libmoneta_util.a
LIBMONETA_CRYPTO=crypto/libmoneta_crypto.a
LIBMONETA_UNIVALUE=univalue/libmoneta_univalue.a
LIBMONETAQT=qt/libmonetaqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libmoneta_crypto.a \
  libmoneta_util.a \
  libmoneta_common.a \
  univalue/libmoneta_univalue.a \
  libmoneta_server.a \
  libmoneta_cli.a
if ENABLE_WALLET
MONETA_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libmoneta_wallet.a
endif

if BUILD_MONETA_LIBS
lib_LTLIBRARIES = libmonetaconsensus.la
LIBMONETA_CONSENSUS=libmonetaconsensus.la
else
LIBMONETA_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_MONETAD
  bin_PROGRAMS += monetad
endif

if BUILD_MONETA_UTILS
  bin_PROGRAMS += moneta-cli moneta-tx
endif

.PHONY: FORCE
# moneta core #
MONETA_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  amount.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compressor.h \
  primitives/block.h \
  primitives/transaction.h \
  core_io.h \
  crypter.h \
  db.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  pow.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script/interpreter.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/script_error.h \
  serialize.h \
  streams.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilstrencodings.h \
  utilmoneystr.h \
  utiltime.h \
  version.h \
  wallet.h \
  wallet_ismine.h \
  walletdb.h \
  compat/sanity.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libmoneta_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between monetad and moneta-qt
libmoneta_server_a_CPPFLAGS = $(MONETA_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libmoneta_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(MONETA_CORE_H)

# wallet: shared between monetad and moneta-qt, but only linked
# when wallet enabled
libmoneta_wallet_a_CPPFLAGS = $(MONETA_INCLUDES)
libmoneta_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  wallet_ismine.cpp \
  walletdb.cpp \
  $(MONETA_CORE_H)

# crypto primitives library
crypto_libmoneta_crypto_a_CPPFLAGS = $(MONETA_CONFIG_INCLUDES)
crypto_libmoneta_crypto_a_SOURCES = \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/rfc6979_hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/scrypt.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/rfc6979_hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/scrypt.h \
  crypto/sha1.h \
  crypto/ripemd160.h

# univalue JSON library
univalue_libmoneta_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp \
  univalue/univalue_escapes.h \
  univalue/univalue.h

# common: shared between monetad, and moneta-qt and non-server tools
libmoneta_common_a_CPPFLAGS = $(MONETA_INCLUDES)
libmoneta_common_a_SOURCES = \
  allocators.cpp \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  $(MONETA_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libmoneta_util_a_CPPFLAGS = $(MONETA_INCLUDES)
libmoneta_util_a_SOURCES = \
  compat/strnlen.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  random.cpp \
  rpcprotocol.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilstrencodings.cpp \
  utilmoneystr.cpp \
  utiltime.cpp \
  $(MONETA_CORE_H)

if GLIBC_BACK_COMPAT
libmoneta_util_a_SOURCES += compat/glibc_compat.cpp
libmoneta_util_a_SOURCES += compat/glibcxx_compat.cpp
endif

# cli: shared between moneta-cli and moneta-qt
libmoneta_cli_a_CPPFLAGS = $(MONETA_INCLUDES)
libmoneta_cli_a_SOURCES = \
  rpcclient.cpp \
  $(MONETA_CORE_H)

nodist_libmoneta_util_a_SOURCES = $(srcdir)/obj/build.h
#

# monetad binary #
monetad_LDADD = \
  $(LIBMONETA_SERVER) \
  $(LIBMONETA_COMMON) \
  $(LIBMONETA_UNIVALUE) \
  $(LIBMONETA_UTIL) \
  $(LIBMONETA_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
monetad_LDADD += libmoneta_wallet.a
endif
monetad_SOURCES = monetad.cpp
#

if TARGET_WINDOWS
monetad_SOURCES += monetad-res.rc
endif

monetad_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
monetad_CPPFLAGS = $(MONETA_INCLUDES)
monetad_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# moneta-cli binary #
moneta_cli_LDADD = \
  $(LIBMONETA_CLI) \
  $(LIBMONETA_UTIL) \
  $(BOOST_LIBS) \
  $(SSL_LIBS) \
  $(CRYPTO_LIBS)

moneta_cli_SOURCES = \
  moneta-cli.cpp

moneta_cli_CPPFLAGS = $(MONETA_INCLUDES)
#

# moneta-tx binary #
moneta_tx_LDADD = \
  $(LIBMONETA_UNIVALUE) \
  $(LIBMONETA_COMMON) \
  $(LIBMONETA_UTIL) \
  $(LIBMONETA_CRYPTO) \
  $(LIBSECP256K1) \
  $(BOOST_LIBS) \
  $(CRYPTO_LIBS)

moneta_tx_SOURCES = moneta-tx.cpp
moneta_tx_CPPFLAGS = $(MONETA_INCLUDES)
#
moneta_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
moneta_cli_SOURCES += moneta-cli-res.rc
endif
moneta_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if BUILD_MONETA_LIBS
include_HEADERS = script/monetaconsensus.h
libmonetaconsensus_la_SOURCES = \
  primitives/transaction.cpp \
  crypto/hmac_sha512.cpp \
  crypto/scrypt.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/ripemd160.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  pubkey.cpp \
  script/script.cpp \
  script/interpreter.cpp \
  script/monetaconsensus.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libmonetaconsensus_la_SOURCES += compat/glibc_compat.cpp
  libmonetaconsensus_la_SOURCES += compat/glibcxx_compat.cpp
endif

libmonetaconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libmonetaconsensus_la_LIBADD = $(CRYPTO_LIBS)
libmonetaconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_MONETA_INTERNAL
if USE_LIBSECP256K1
libmonetaconsensus_la_LIBADD += secp256k1/libsecp256k1.la
endif
endif

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
