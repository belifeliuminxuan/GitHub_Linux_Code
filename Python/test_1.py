 ###########################################################
 # Author   : liuminxuan
 # Email    : liuminxuan1024@163.com
 # Time     : 2020-02-20 09:33
 # FileName : test_1.py
 ###########################################################


# res = bin(int('BDACD',16))
# print(res)


import datetime
today = datetime.date.today().strftime('%Y{}%m{}%d{}').format(*'年月日')
print('今天是：' + today)
