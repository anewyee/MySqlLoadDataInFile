# MySql-LOAD-DATA-INFILE
加载文件到数据库，每个加载任务独立线程。

# yinxiang
## MySql-LOAD-DATA-INFILE-by-Qt-线程处理项目

- 实例：https://github.com/drWebber/MySql-LOAD-DATA-INFILE-by-Qt

- 帮助理解地址： Qt之QThread（深入理解） http://blog.csdn.net/liang19890820/article/details/52186626

http://mobile.51cto.com/symbian-271567.htm

- 数据库操作
    - Qt数据库 QSqlTableModel实例操作
    - Qt数据库 QSqlQueryModel实例操作 上篇
    - Qt数据库 QSqlQueryModel实例操作 下篇

- 设置密码；

- 建立数据库，参考文件夹中bigData.sql文件；

CREATE TABLE `chartlist` (
  `Title` varchar(255) NOT NULL,
  `Scale` int(11) NOT NULL DEFAULT '0',
  `Edition Date` date DEFAULT NULL,
  `Folio` varchar(20) DEFAULT NULL,
  `Disk` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `orders` (
  `id` int(10) UNSIGNED NOT NULL,
  `date` date NOT NULL,
  `count` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

CREATE TABLE `products` (
  `id` int(10) UNSIGNED NOT NULL,
  `article` varchar(30) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `count` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

- MYSQL导出数据出现The MySQL server is running with the --secure-file-priv option so it cannot execute this
- E:/svn/QualityControlSystem/MySql-LOAD-DATA-INFILE-by-Qt-master/products.txt

我正在学习MySQL并尝试使用 LOAD DATA 子句。当我使用它如下：

  LOAD DATA INFILE“text.txt”INTO table mytable;

我收到以下错误：

MySQL服务器正在使用--secure-file-priv选项运行，因此无法执行此语句

今天尝试使用 into outfile导出数据的时候出现错误：
The MySQL server is running with the --secure-file-priv option so it cannot execute this statement
上网查了一下，应该是mysql设置的权限，可以使用
show variables like '%secure%';查看 secure-file-priv 当前的值是什么

导出的数据必须是这个值的指定路径才可以导出，默认有可能是NULL就代表禁止导出，所以需要设置一下

知道mysql安装路径下的my.ini文件，设置一下路径：到自己导入文件的路径

# Secure File Priv.
secure-file-priv="E:/svn/QualityControlSystem/MySql-LOAD-DATA-INFILE-by-Qt-master"

然后重启数据库即可；

- secure_file_priv mysqld 用这个配置项来完成对数据导入导出的限制

例如我们可以通过 select * from tempdb.t into outfile '/home/mysql/t.txt'; 把tempdb.t 表的数据导出来；这个导出操作可以面临如下问题

1、任何一个mysql用户只要它能执行上面的sql语句、并且执行成功；那么它就把文件写到了/home/mysql/目录下？

  如果有一个坏人他一直导出数据到文件目录，那么总有一天会被写满的！

2、没有办法限制只能把文件导出到/tmp/目录
我们可以通过secure_file_priv 来完成对导入|导出的限制

secure_file_priv

　　1、限制mysqld 不允许导入 | 导出

　　　 mysqld --secure_file_prive=null

　　2、限制mysqld 的导入 | 导出 只能发生在/tmp/目录下

　　　 mysqld --secure_file_priv=/tmp/

　　3、不对mysqld 的导入 | 导出做限制

cat /etc/my.cnf
　　　　[mysqld]
　　　　secure_file_priv
