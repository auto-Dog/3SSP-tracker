# 3SSP-tracker
3 support solar pannel tracker(with arduino)
## 标准版本
_待填坑_
## 测试版本：此版本为测试功率数据所用
特性：
1. 抛弃RTC时钟模块，改用内部计时
2. 测量装置实验对照组切换开关，中断方式每分钟切换一次（存疑，误差累积放大）
3. 主控制用mills定时取代delay，并修复大数延迟时存在的bug
4. 每六分钟驱动一次电机<br>
_建议调整至高度600_
