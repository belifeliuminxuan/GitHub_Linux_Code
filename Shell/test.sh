#!/bin/bash 
#ls -a
#read -p '请输入需要创建的C源文件的名称:'Filename
read Filename
touch $Filename.c
echo "#include <stdio.h>">$Filename.c
echo "#include <unistd.h>">$Filename.c
echo "#include <fcntl.h>">$Filename.c

ls -lrt


