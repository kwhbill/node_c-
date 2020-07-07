// test.js
const addon = require('./build/Release/addon');

console.log('This should be eight:', addon.Add(3, 5));   // 调用 c++ 
addon.RunCallback((msg) => {   // c++ 回调
  console.log(msg);
});
var fn = addon.CreateFunction()  // 创建函数 
console.log(fn(),'CreateFunction');



