# 问题

1. 在vs工程中添加文件编译会导致报错的解决方法：
	将除了qtpropertybrowserutils_p.h之外的头文件全部选中并右击，在配置属性中更改moc的Dynamic C++ Source为Disable即可