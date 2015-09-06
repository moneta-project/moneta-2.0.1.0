Moneta Core integration/staging tree
=====================================

https://moneta.io

What is Moneta?
----------------

Moneta is an experimental new digital currency that enables instant payments to
anyone, anywhere in the world. Moneta uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Moneta Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the Moneta Core software, see https://moneta.io

License
-------

Moneta Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Moneta
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](https://groups.google.com/forum/#!forum/moneta-dev).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see [doc/coding.md](doc/coding.md)) or are
controversial.

The `master-0.10` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/moneta-project/moneta/tags) are created
regularly to indicate new official, stable release versions of Moneta.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Manual Quality Assurance (QA) Testing

Large changes should have a test plan, and should be tested by somebody other
than the developer who wrote the code.
See https://github.com/moneta/QA/ for how to create a test plan.

Translations
------------

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

We only accept translation fixes that are submitted through [Moneta Core's Transifex page](https://www.transifex.com/projects/p/moneta/).
Translations are converted to Moneta periodically.

First install
-------------

### Swap file 2048k

    $ sudo install -o root -g root -m 0600 /dev/null /swapfile

    $ dd if=/dev/zero of=/swapfile bs=1k count=2048k

    $ mkswap /swapfile

    $ swapon /swapfile

    $ echo "/swapfile       swap    swap    auto      0       0" | sudo tee -a /etc/fstab

    $ sudo sysctl -w vm.swappiness=10

    $ echo vm.swappiness = 10 | sudo tee -a /etc/sysctl.conf

**Unix terminal**

    $ sudo apt-get install build-essential

    $ sudo apt-get install libssl-dev

    $ sudo apt-get install libminiupnpc-dev (see USE_UPNP compile flag)

    $ sudo apt-get install libqt4-dev libprotobuf-dev protobuf-compiler

    $ sudo apt-get install build-essential libboost-all-dev libcurl4-openssl-dev libdb5.1-dev libdb5.1++-dev git qt-sdk libminiupnpc-dev libtool

    $ sudo apt-get install libqrencode-dev

    $ git clone https://github.com/moneta-project/moneta

    $ cd moneta

    $ bash ./autogen.sh

    $ bash ./make.sh

Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging messages are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play monetas" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode, blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regtest mode.

**DEBUG_LOCKORDER**

Moneta Core is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of which locks
are held, and adds warnings to the debug.log file if inconsistencies are detected.

Tricks
------
    $ sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
    $ sudo apt-get install libqt4-dev libprotobuf-dev protobuf-compiler

