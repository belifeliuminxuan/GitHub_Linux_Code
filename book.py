import requests
from time import sleep
from lxml import etree


def save_data(data):
    for msg in data:
        msg_str = msg['book_title'] + ',' + msg['book-author'] + ',' + msg['book-publish'] + ',' + msg[
            'book-publish_time'] + ',' + msg['book-descrip'] + ',' + msg['book-price'] + ',' + msg['book-pinglun']
        print(msg_str)
        with open('dangdang.csv', 'a', encoding='utf-8') as f:  # 写入文件
            f.write(msg_str)
            f.write('\n')


class dangdang_spider:
    # 定义爬虫类
    def __init__(self):
        self.url = "http://category.dangdang.com/pg{}-cp01.00.00.00.00.00.html"  # 爬虫网址
        self.headers = {  # 设置headers
            'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                          'Chrome/56.0.2924.87 Safari/537.36'}

    # 爬取基本网页信息
    def parse(self, url):
        r = requests.get(url, headers=self.headers)
        return r.content.decode(encoding='gbk')

    # 对数据处理
    def handle_data(self, data, i):
        html = etree.HTML(data)  # 对信息进行html格式化
        msg_list = []
        li_list = html.xpath("// ul[ @ id = 'component_0__0__6612']/li")  # 利用xpath锁定图书信息所在的html标签
        for li in li_list:
            msg = {'book_title': li.xpath('./p/a/text()')[0],
                   'book-author': li.xpath('./p/span[1]/a[1]/@title')[0] if len(
                       li.xpath('./p/span[1]/a[1]/@title')) > 0 else '无',
                   'book-publish': li.xpath('./p/span[3]/a/text()')[0] if len(
                       li.xpath('./p/span[3]/a/text()')) > 0 else '无',
                   'book-publish_time': li.xpath('./p[5]/span[2]/text()')[0].replace(' /', '') if len(
                       li.xpath('./p[5]/span[2]/text()')) > 0 else '无',
                   'book-descrip': li.xpath('./p[2]/text()')[0] if len(li.xpath('./p[2]/text()')) > 0 else '无',
                   'book-price': li.xpath('./p[3]/span[1]/text()')[0], 'book-pinglun': li.xpath('./p[4]/a/text()')[0]}
            msg_list.append(msg)
        # print(msg_list)

        next_url = self.url.format(i)  # 构建下一页url
        return msg_list, next_url

    def run(self):
        i = 1
        next_url = self.url.format(i)
        while next_url:
            html_str = self.parse(next_url)
            i = i + 1
            msg_list, next_url = self.handle_data(html_str, i)
            save_data(msg_list)
            print(next_url)
            sleep(2)


if __name__ == '__main__':
    d = dangdang_spider()
    d.run()

