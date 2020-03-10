 ###########################################################
 # Author   : liuminxuan
 # Email    : liuminxuan1024@163.com
 # Time     : 2020-02-20 21:13
 # FileName : tar.sh
 ###########################################################

 read date_
tar -zcvf $date_.tar  test_*.c  
rm -rf *.c 
echo "打包完毕!"
ls -lrt
