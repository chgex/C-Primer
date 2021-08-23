/*
 * @Author: liubai
 * @Date: 2021-08-23 
 * @LastEditTime: 2021-08-23 
 */
#include<iostream>
#include "Sales_item.h" //std，用<>，自定义用""

int main(){
    Sales_item total;
    //读取第一条记录
    if(std::cin >> total){
        Sales_item trans;
        //读取下一条记录
        while(std::cin >> trans){
            if (total.isbn()==trans.isbn())
                //更新总销售额
                total+=trans;
            else{
                //下一本书
                std::cout<<total<<std::endl;
                total=trans;
            }
        }
        std::cout<<total<<std::endl;
    }else{
        //输入有误
        std::cerr << "No Data?!"<<std::endl;
        return -1;
    }
    return 0;
}