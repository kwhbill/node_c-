// addon.cc
#include <node.h>

namespace demo
{

  using v8::Context;
  using v8::Exception;
  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::FunctionTemplate;
  using v8::Isolate;
  using v8::Local;
  using v8::NewStringType;
  using v8::Null;
  using v8::Number;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void Add(const FunctionCallbackInfo<Value> &args)
  {
    Isolate *isolate = args.GetIsolate();

    // 检查传入的参数的个数。
    if (args.Length() < 2)
    {
      // 抛出一个错误并传回到 JavaScript。
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate,
                              "参数的数量错误",
                              NewStringType::kNormal)
              .ToLocalChecked()));
      return;
    }

    // 检查参数的类型。
    if (!args[0]->IsNumber() || !args[1]->IsNumber())
    {
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate,
                              "参数错误",
                              NewStringType::kNormal)
              .ToLocalChecked()));
      return;
    }

    // 执行操作
    double value =
        args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
    Local<Number> num = Number::New(isolate, value);

    // 设置返回值 (使用传入的 FunctionCallbackInfo<Value>&)。
    args.GetReturnValue().Set(num);
  }
  void RunCallback(const FunctionCallbackInfo<Value> &args)
  {
    Isolate *isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cb = Local<Function>::Cast(args[0]);
    const unsigned argc = 1;
    Local<Value> argv[argc] = {
        String::NewFromUtf8(isolate,
                            "hello world",
                            NewStringType::kNormal)
            .ToLocalChecked()};
    cb->Call(context, Null(isolate), argc, argv).ToLocalChecked();
  }
  void CreateObject1(const FunctionCallbackInfo<Value> &args)
  {
    Isolate *isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    Local<Object> obj = Object::New(isolate);
    obj->Set(context,
             String::NewFromUtf8(isolate,
                                 "msg",
                                 NewStringType::kNormal)
                 .ToLocalChecked(),
             args[0]->ToString(context).ToLocalChecked())
        .FromJust();

    args.GetReturnValue().Set(obj);
  }

  void MyFunction(const FunctionCallbackInfo<Value> &args)
  {
    Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(
                                  isolate, "hello world", NewStringType::kNormal)
                                  .ToLocalChecked());
  }

  void CreateFunction(const FunctionCallbackInfo<Value> &args)
  {
    Isolate *isolate = args.GetIsolate();

    Local<Context> context = isolate->GetCurrentContext();
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyFunction);
    Local<Function> fn = tpl->GetFunction(context).ToLocalChecked();

    // 可以省略这步使它匿名
    fn->SetName(String::NewFromUtf8(
                    isolate, "theFunction", NewStringType::kNormal)
                    .ToLocalChecked());

    args.GetReturnValue().Set(fn);
  }

  void Init(Local<Object> exports, Local<Object> module)
  {
    NODE_SET_METHOD(exports, "Add", Add);
    NODE_SET_METHOD(exports, "RunCallback", RunCallback);
    NODE_SET_METHOD(exports, "CreateObject1", CreateObject1);
    NODE_SET_METHOD(exports, "CreateFunction", CreateFunction);
  }

  NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

} // namespace demo