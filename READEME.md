# c++插件  [Node文档](http://nodejs.cn/api/addons.html#addons_building "c++")

* 新建 addon.cc ,写 c++ 方法
* 它必须被编译成二进制 addon.node 文件 ，需创建一个名为 binding.gyp 的文件
* node-gyp（一个用于编译 Node.js 插件的工具），npm install -g node-gyp 命令进行安装
* node-gyp configure 为当前平台生成相应的项目构建文件
* node-gyp build 命令生成编译后的 addon.node 的文件。 它会被放进 build/Release/ 目录
* 通过 require() 构建后的 addon.node 模块
