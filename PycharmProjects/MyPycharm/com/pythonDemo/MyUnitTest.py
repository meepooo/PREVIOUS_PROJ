import re

import requests

if __name__ == "__main__":
    print("hello python")

    keyword = input("输入关键字：")
    response  = requests.get("http://pic.sogou.com/pics?query="+keyword+"=05009900&p=40030501&_asf=pic.sogou.com&_ast=1543190407&sc=index&sut=11432&sst0=1543190406722")

    # print("content" + str(response.content))
    print(response.text)

    # while True:
    #     for addr in re.findall('"thumbUrl":"(.*?)"',str(response.text),re.S):
    #         print(addr)


    # response1 = requests.get(addr[0])
    # print(response1.text)
