# VS项目配置

## 配置属性

#### 常规：

```
    输出目录：$(SolutionDir)\bin\$(Platform)\$(Configuration)\
    
    中间目录：$(SolutionDir)\bin\intermediates\$(Platform)\$(Configuration)\
```



#### 调试：

```
工作目录：$(ProjectDir)\depends
```



#### C/C++：

```
附加包含目录：C:\Users\69017\Desktop\UFO\UFO\include
```



#### 链接器：

```
附加库目录：C:\Users\69017\Desktop\UFO\UFO\depends
附加库目录：C:\Users\69017\Desktop\UFO\UFO\lib

附加依赖项：	CSCInterface.lib
			ids_peak_comfort_c.lib
			PI_GCS2_DLL.lib
```



#### PI_GCS2_DLL函数报错处理：

```
C/C++ --> 预编译头 --> 预编译头 --> 输入：PI_DLL_EXPORTS
```





## IDE版本

#### 编译器

**vs2022**

**Qt：5.12.12**



#  逻辑编写

