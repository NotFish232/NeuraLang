# neuralang: A Compiled Interoperable Scripting Language Built for Machine Learning

![demo1](./readme/demo1.png)

_neuralang_ as a compiled language with support for interoperability with any LLVM language (i.e. C, C++, Haskell, Rust, etc.) with a focus on machine learning.

Modern day machine learning is all done on python, making not very extendable - good luck trying to have Rust and Python communicate with each other without having two separate processes running.  _neuralang_ seeks to solve this by making a scripting language built in LLVM (low level virtual machine) - allowing anybody with knowledge in most modern languages to have access to machine learning embedded in _their_ program without the need for creating multiple programs to have concurrent machine learning.
