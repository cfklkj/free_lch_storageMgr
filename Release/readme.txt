简单物品管理程序--说明

1.物品信息栏可以右键添加或删除
        物品序号需要字符需要大于3个字符
     

2.入库信息只有添加功能
      物品序号必须在物品信息中已添加
      数量信息必须大于1
	
3.出库信息只有添加功能
      物品序号必须在物品信息中已添加
      数量信息必须大于1

4.添加入库信息时 物品信息的余量会增加
   添加出库信息时 物品信息的余量会减少

警告：添加的信息请勿使用 逗号 符号（，）  否者会引起数据错误

--2019-6-10
1.物品信息添加的类型格式优化

2.添加查询功能
查询出库信息：
单个条件查询-如-   登记人=25
多个条件查询-如-   登记人=25,出库日期=2019-06-03,领用人=34
什么条件都没有则显示全部数据

注：数量作为查询条件无效
    若查询条件无效将被忽略
    不支持模糊查询
 
2016-6-11
1.出入库添加备注功能   -- 若有备注,双击将弹出备注对话框

