
// cmd_region_client.h

#ifndef __CMD_REGION_CLIENT_H__
#define __CMD_REGION_CLIENT_H__
#ifndef _MJ_NEW
const char GAME_COPY_RIGHT =95;//游戏版本号
#else
const char GAME_COPY_RIGHT =107;//游戏版本号
#endif
/* chat channel type */
const char CHAT_CHANNEL_NORMAL  = 1;//普通
const char CHAT_CHANNEL_TEAM    = 2;//团队
const char CHAT_CHANNEL_PARTY   = 3;//公会
const char CHAT_CHANNEL_BROTHER = 4;//兄弟
const char CHAT_CHANNEL_TOP		= 5;//停留在头顶
const char CHAT_CHANNEL_PRIVATE = 6;//私语
const char CHAT_CHANNEL_SYSTEM  = 7;//系统//0-100对应strChatPromptInfo[]，>100预留
const char CHAT_CHANNEL_ITEM_INFO	= 8;//道具信息
const char CHAT_CHANNEL_NPC_SAY		= 9;//ncp say

const char CHAT_CHANNEL_CRY			= 10; //大喊频道
const char CHAT_CHANNEL_FRIEND		= 11;//好友频道
const char CHAT_CHANNEL_FRIEND_MY   = 12;//我的好友
const char CHAT_CHANNEL_WORLD		= 13;
const char CHAT_CHANNEL_MAX			= 14;//频道不能大于CHAT_CHANNEL_MAX

const char CHAT_CHANNEL_ERRORREPORT = 40;//出错信息返回服务器

const char CHAT_CHANNEL_NPCTYPE_SAY		= 20;//npc类型说话
const char CHAT_CHANNEL_LIUYANBAN		= 21;//留言板
//一些闲话
const char SAY_FIGHT_CALL	= 30;//战斗说话 say,请求支援

const char SYSTEM_MESSAGE_LUA = 1;

/* sync flag */
const char SYNC_FLAG_COMPLEX_MODEL	= 1;
const char SYNC_FLAG_POSITION		= 2;
const char SYNC_FLAG_DIRECTION		= 4;
const char SYNC_FLAG_USER			= 8;
const char SYNC_FLAG_TASK_NPC		= 16;
const char SYNC_FLAG_STATIC			= 32;

// const char MOVE_STATE_VEH		= 8;



//#pragma message("简短命令改成char型")

//base yes no//具体作用在代码里体现，主要判断有无
const char EVENT_YES				= 1;
const char EVENT_NO					= 2;
const char EVENT_TEMP				= 3;
const char EVENT_NO_COPYMAP			= 4;//没有副本了

const char SCRIPT_SCENE				= 1;//场景脚本
const char SCRIPT_NPC				= 2;//暂时两个
const char SCRIPT_TASK_START		= 3;//领取任务脚本
const char SCRIPT_TASK_AWARD		= 4;//奖励任务脚本
const char SCRIPT_TASK_CANCEL		= 5;//取消正在进行的任务
const char SCRIPT_TASK_MAPTIME		= 6;//校正地图正在进行的任务时间
const char SCRIPT_TASK_NOMAPTIME	= 7;//取消地图正在进行的任务时间

const char SCRIPT_MONEY	= 8;//呐喊-钱
const char SCRIPT_TASK_STATEERROR		= 9;//任务额外状态不能完成

const char SCRIPT_CHANGEITEM	= 11;//使用传送道具

const char SCRIPT_LEVEL_JIANGLI			= 18;	//等级奖励

const char SCRIPT_CHENGMI_INFO		= 31;//
const char SCRIPT_CHENGMI_INFO_TAR	= 34;//他人防沉迷

const char TASK_STATEERROR_TONGSHUAI	= 100;//任务额外状态不能完成以有统帅在


const char OK_JIANGLI				= 1;	//
const char ERROR_JIANGLI_LEVEL		= 2;	//级别不够
const char ERROR_JIANGLI_ED			= 3;	//已经做过

//宠物专用
const char PET_ATTACK		= 1;		// 攻击
//const char PET_NO_ATTACK	= 2;		// 
const char PET_FOLLOW		= 2;		//跟随主人 
const char PET_STOP			= 3;		// 宠物置于只挨打不攻击状态
//const char PET_OUR_ROUND	= 3;		// 到主人身边
const char PET_SKILL		= 4;		// 使用宠物技能
const char PET_DELETE		= 5;		// 回收宠物


const char GAME_SERVER_MAIN			= 1;		//主服务器
const char GAME_SERVER_COPY			= 2;		//副本服务器
const char GAME_SERVER_FACTION		= 3;		//公会服务器
const char GAME_SERVER_MAX			= 4;		//Max服务器

const short EVENT_LEVEL_UP			= 1;
const short EVENT_CHANGE_HEAD		= 2;
const short EVENT_CHANGE_SCENE		= 3;
const short EVENT_LEAVE_GAME		= 4;

const char NEW_EVENT_CHENMI_CHECK					=11;//沉迷检查

//exchange_item
const char EXCHANGE_NONE			= 0;//无此人
const char EXCHANGE_ERROR			= 1;//失败提示
const char EXCHANGE_CANCEL			= 2;
//const char EXCHANGE_INPUTOK			= 3;
const char EXCHANGE_ENDOK			= 4;
const char EXCHANGE_REQUEST			= 5;//请求交易
//const char EXCHANGE_ALLOW			= 6;//答应交易allow 
//const char EXCHANGE_REFUSE			= 7;//拒绝交易refuse
const char EXCHANGE_UPDATE			= 8;//对方更新交易栏的道具
const char EXCHANGE_UPDATE_MONEY	= 9;//对方更新交易栏的金钱数
//const char EXCHANGE_OPEN			= 10;//打开交易
//const char EXCHANGE_CLOSE			= 11;//关闭交易

const char EXCHANGE_QUERYALLOK		= 10;
const char EXCHANGE_ALLOK			= 11;	//全部都好了
const char EXCHANGE_ALLCANCEL		= 12;
const char EXCHANGE_CHANGECANCEL	= 13;	


//shop item
const char SHOP_BUY					= 1;//买
const char SHOP_SELL				= 2;//卖
const char SHOP_REPAIR				= 3;//修复//客户端预判断使用
const char SHOP_REPAIR_EQUIP		= 4;//修复装备栏
const char SHOP_REPAIR_PACK			= 5;//修复背包栏
const char SHOP_REPAIR_ALL			= 6;//修复背包栏全部
const char SHOP_LIFA				= 7;//理发
const char SHOP_RANFA				= 8;//染发

const char SHOP_VIPBUY				= 9;//vip买入
const char SHOP_UNIONBUY			= 10;//工会买入

const char JIFEN_SHOP				= 11;//积分商城


const char MYSELL_START				= 1;	//开始摆摊
const char MYSELL_END				= 2;	//收摊
const char MYSELL_UPDATEMONEY		= 3;	//更新价格
const char MYSELL_BUYITEM			= 4;	//购买物品
//const char MYSELL_MESSAGE			= 5;	//留言
const char MYSELL_LOOK				= 6;	//查看摊位信息

//const char MYSELL_ADDITEM			= 6;	//添加摆摊物品
//const char MYSELL_DELITEM			= 7;	//下架


const char CHANGE_PK                = 7;	//修改PK状态 呵呵 居然放到这里了
const int MAX_PK_OFFSET				= 10;
const int MIN_PK_LEVEL				= 20;	

const char WUQI_ATTACK_THROWSTONE_START				= 1;	//投石车开始投石
const char WUQI_ATTACK_THROWSTONE_END				= 2;	//投石车投到目标点



const char WUQI_ATTACK_USESKILL				= 100;	//聚气攻击/群攻暂时放这里

//ITEM_EQUIP = 0,
//ITEM_PACK  = 1,
// task
/*const char TASK_START				= 1;//领取任务
const char TASK_AWARD				= 2;//奖励任务
const char TASK_ITEM				= 3;//过场景奖励任务

const char TASK_OVER				= 4;//以完成的任务
const char TASK_RUN					= 5;//正在进行的任务
const char TASK_CANCEL				= 6;//取消正在进行的任务
const char TASK_ADD					= 7;//杀死一个怪物
*/
const char GUOZHAN_START			= 1;//国战开始
const char GUOZHAN_END				= 2;//国战结束
const char GUOZHAN_JUDIAN_DEAD		= 3;//国战一个据点被打
const char GUOZHAN_ADDGONGXUN		= 4;//国战人数击破,更新功勋客户端记
const char GUOZHAN_GUOJIAGONGXUN	= 5;//国战更新国家功勋
const char GUOZHAN_GUOJIAGEREN		= 6;//国战当前国家个人最大功勋//提示用

const char GONGCHENG_START			= 11;//攻城战开始
const char GONGCHENG_END			= 12;//攻城战结束
const char GONGCHENG_GONGXUN		= 13;//攻城战战更新国家功勋


//cim
const char CIM_REQUEST					= 1;//请求
const char CIM_ALLOW					= 2;//同意
const char CIM_REFUSE					= 3;//拒绝
const char CIM_EXIT						= 4;//退出

//team
const char TEAM_CREATE					= 1;//创建
const char TEAM_REQUEST					= 2;//邀请
const char TEAM_ALLOW					= 3;//同意
const char TEAM_REFUSE					= 4;//拒绝
const char TEAM_LEAVE					= 5;//离队
const char TEAM_JOIN					= 6;//加入
const char TEAM_DELETE					= 7;//解散
const char TEAM_INFO					= 8;//全部信息
const char TEAM_HAVE					= 9;//已有队伍
const char TEAM_OUT						= 10;//赶出队伍
const char TEAM_UPDATA					= 11;//刷新位置
const char TEAM_LEVEL_OUT				= 12;//等级超出
const char TEAM_SETCAP					= 13;//设置队长
const char TEAM_NOTFIND					= 14;//邀请的对象找不到
const char TEAM_CHANGEITEMSHARE			= 15;//更换物品分配方式
const char TEAM_CHANGEEXPSHARE			= 16;//更换经验分配方式

const char OBJECT_USER					= 1;	// 人物
const char OBJECT_ITEM					= 2;	// 物品
const char OBJECT_EFFECT				= 3;	// 效果 地表上的效果(CFloorEffect)
const char OBJECT_BODY_EFFECT			= 4;	// 效果 身体上的效果(CFloorEffect)
const char OBJECT_BODY_BACK				= 5;	// 变身回来
const char OBJECT_BOSS_BIANSHEN			= 6;	// BOSS变身
const char OBJECT_PLAYER_BIANSHEN		= 7;	// Player变身
const char OBJECT_ADD_BODY_EFFECT		= 8;	// 向身上添加效果
const char OBJECT_DIYUHUO_BIANSHEN		= 9;	// 地狱火变身
const char OBJECT_DIYUHUO_BACK			= 10;	// 地狱火变身变身回来

const char OBJECT_NEWPLAYER_BIANSHEN	= 11;	// 新的人物变身
const char OBJECT_NEWPLAYER_BACK		= 12;	// 新的人物变身回去

const char OBJECT_SKILL_EFFECT			= 13;	// 技能效果
const char OBJECT_CLEARALL_EFFECT		= 14;	// 清除技能效果
//离开游戏
const char LEAVEGAME_ALL					= 1;//完全离开游戏
const char LEAVEGAME_SELECT					= 2;//离开游戏到选人界面
const char LEAVEGAME_PWD					= 3;//离开游戏到//到账号密码完全关闭就可以了

//login server//为了加快速度列举所有
const char LOGIN_NAME_ERROR					= 1;//名字错误
const char LOGIN_PWD_ERROR					= 2;//密码错误
const char LOGIN_IN_OK						= 3;//登入成功
const char LOGIN_CREATE						= 4;//创建角色
const char LOGIN_CREATE_OK					= 5;//创建角色成功
const char LOGIN_CREATE_ERROR				= 6;//创建角色失败
const char LOGIN_DELETE						= 7;//删除角色
const char LOGIN_DELETE_OK					= 8;//删除角色成功
const char LOGIN_DELETE_ERROR				= 9;//删除角色失败
const char LOGIN_LOGIN_IN					= 10;//账号使用中

const char LOGIN_ROLE_ERROE					= 11;//读取人物错误

const char LOGIN_COPY_ERROE					= 12;//版本错误
const char LOGIN_SELECT_ROLE				= 13;//选择人物进入游戏

const char LOGIN_CREATE_ERROR_NAME			= 14;//创建角色失败昵称已存在

const char LOGIN_SERVERSTART_ERROE			= 15;//服务器还未启动
const char LOGIN_USER_STOP					= 16;//账号未激活
const char LOGIN_USER_MORE					= 17;//人数太多

const char LOGIN_USER_STOPTIME				= 18;//被封停一段时间

const char LOGIN_IN_OK_SELECT				= 19;	//登入成功

const char LOGIN_USER_DELAYTIME				= 20;//登入受限一段时间

const char LOGIN_IN_OK_PWD					= 21;	//登入成功但需要输入额外密码

const char LOGIN_IN_OK_REAL					= 22;	//real密码验证成功
const char LOGIN_IN_ERROR_REAL				= 23;	//real密码验证错误
const char LOGIN_DB_ERROR				    = 24;	// sammy

const char LOGIN_IN_ERROR_HF				= 25;	//haofang密码验证失败
const char LOGIN_IN_OK_MATRIX				= 26;//登入成功但需要输入矩阵卡

const char LOGIN_IN_OK_PASSPORD				= 29;//验证通行证成功
const char LOGIN_IN_ERROR_PASSPORD			= 30;

const char LOGIN_IN_BIND_MACINFO			= 33;	//mac绑定信息

const char LOGIN_USER_STOP_BY_CALL			= 34;	//电话密保
const char LOGIN_USER_FROZEN				= 36;	//冻结

const char LOGIN_IN_OK_REAL_BUT_NO_CHENGREN	= 38;	//验证成功但是非成人不得游戏

const char LOGIN_IN_OK_XUNLEI					= 50;	//real密码验证成功
const char LOGIN_IN_ERROR_XUNLEI				= 51;	//real密码验证错误

const char LOGIN_IN_BACKUP_STATE			= 52;	//数据处于备份状态 add by coke 2009041300
// replication update type 
//add by coke 20090731
const char USER_STATE_LOCK						=1;	//永久封停
const char USER_STATE_LOCK_BY_TIME				=2;	//临时封停
const char USER_STATE_LOCK_BY_TJ0				=3;	//脱机封停
const char USER_STATE_LOCK_BY_TJ1				=4;	//脱机封停
const char USER_STATE_LOCK_BY_CALL				=5;	//电话密保
const char USER_STATE_FROZEN					=10;//冻结
//end by coke 20090731
//


const char REP_UPDATE_ALL  		= 0;
const char REP_UPDATE_BASE 		= 10;
const char REP_UPDATE_TMP  		= 11;//更新一些需要的信息
const char REP_UPDATE_TMP2 		= 12;
const char REP_UPDATE_ADD  		= 13;
const char REP_UPDATE_DELETE	= 14;
const char REP_UPDATE_TASKCRE		= 15;//更新任务对象
const char REP_UPDATE_TASKRAND		= 16;//更新随机任务
const char REP_UPDATE_IMPACTTIME	= 17;//更新效果时间

const char REP_UPDATE_ROUND  		= 13;//更新一些需要的信息给周围的玩家
const char REP_UPDATE_ROUND_BASE  		= 14;//更新一些需要的信息给周围的玩家
const char REP_UPDATE_TMP3 		= 15;
const char REP_UPDATE_ROUND_TMP  		= 16;//更新一些需要的信息给周围的玩家

const char REP_UPDATE_DURABILITY 		= 20;//修正耐久的
const char REP_UPDATE_REPAIRALL 		= 21;//修复所有耐久
const char REP_UPDATE_MAJIANG = 22;
const char REP_UPDATE_KEYSAVE = 23;
const char REP_UPDATE_KEYSAVE_SINGLE = 24;
//join sys
//0合并数量，1嵌入宝石
const char JOIN_NET_NORMAL					= 1;//合成
const char JOIN_NET_QIANRU					= 2;//嵌入
const char JOIN_NET_QIANGHUA				= 3;//强化道具
const char JOIN_NET_DADONG					= 4;//打洞
const char JOIN_NET_XISHOU					= 5;//吸收
const char JOIN_NET_DIEJIA					= 6;//叠加
const char JOIN_NET_BAIFEN					= 7;//肯定成功

const char JOIN_NET_LEAVEITEM				= 8;//分割
const char JOIN_NET_KEYBOX					= 9;//盒子开锁

const char JOIN_NET_RANDATTR				= 10;//属性重洗
const char JOIN_NET_FANGUP				= 11;//防具强化
const char JOIN_NET_LIFEUP				= 12;//增加燃点

const char JOIN_NET_RUNSCRIPT				= 13;//跑脚本

const char JOIN_NET_XISHOU_EXP				= 14;//吸收经验

const char JOIN_NET_CLEARATTR				= 15;//
const char JOIN_NET_PETEXP					= 16;//

const char JOIN_NET_TIANSHEN				= 17;//

const char JOIN_NET_BANGDING					= 18;//bangding

const char JOIN_NET_WEAPON_UP					= 19;//武器强化

const char JOIN_NET_OTHER_ATTR_RESORT			= 20;//额外属性重新排列

const char JOIN_NET_XISHOU_SHEN_QI				= 21;//神器吸收

const char JOIN_NET_PETFOOD					= 31;//petfood
const char JOIN_NET_ATOB					= 32;//a to b

// 生活技能相关
const char LIFESKILL_COLLECT		= 1;	// 采集
const char LIFESKILL_COMPOS			= 2;	// 合成
const char LIFESKILL_FJ				= 3;	//分解
const char LIFESKILL_SP				= 4;	//抚摸

const char LIFESKILL_PEIFANG_UPDATE = 5;	//更新配方
const char LIFESKILL_PEIFANG_UPDATE_SINGLE = 6;	//更新配方
const char LIFESKILL_DELBLOCK = 7;
const char LIFESKILL_SETBLOCK = 8;		

const char LIFESKILL_YUEGUANG = 9;			//月光宝盒


const char ERROR_YUEGUANG_NOFIND = 10;		//要合成的东西找不到
const char ERROR_YUEGUANG_FULL = 11;		//包满了
const char ERROR_YUEGUANG_NOSOURCE = 12;	//材料不够
const char ERROR_YUEGUANG_USEFAIL = 13;		//合成失败了

/*
const char LIFESKILL_COLLECT_START		= 1;	// 开始采集
const char LIFESKILL_COLLECT_CANCEL		= 2;	// 取消采集
const char LIFESKILL_COLLECT_FINISH		= 3;	// 采集结束(c->s)
const char LIFESKILL_COLLECT_SUCCESS	= 4;	// 成功采集(s->c)
const char LIFESKILL_COLLECT_FAILD		= 5;	// 采集失败(s->c)
*/
const char LIFESKILL_COLLECT_START		= 11;	// 开始采集
//const char LIFESKILL_COLLECT_CANCEL		= 12;	// 取消采集//走动自动结束
const char LIFESKILL_COLLECT_FINISH		= 13;	// 采集结束(c->s)
const char LIFESKILL_COLLECT_SUCCESS	= 14;	// 成功采集(s->c)
const char LIFESKILL_COLLECT_FAILD		= 15;	// 采集失败(s->c)

const char LIFESKILL_QUANPIN			= 16;	// 全屏技能

const char LIFESKILL_BREAK_SOUL			= 17;	// 灵魂分解

const char LIFESKILL_COMBIN_SHENQI_RT	= 18;	// 神器合成反馈

const char LIFESKILL_REPAIR_ITEM		= 19;	// 修理药剂

const char LIFESKILL_COMPOS_COMBIN = 1;

const char LIFESKILL_FJ_FJITEM_BYNPC = 1;		//npc分解
const char LIFESKILL_FJ_FJITEM_BYGUILD = 2;		//公会分解


/* region send to client */
const short r2c_base				= 1000;
const short r2c_login_ret			= r2c_base + 1;
const short r2c_chat				= r2c_base + 2;
const short r2c_begin_see			= r2c_base + 3;		//开始看见物件
const short r2c_end_see				= r2c_base + 4;		//结束看见物件
const short r2c_snapshot			= r2c_base + 5;

const short r2c_walk_to				= r2c_base + 7;
const short r2c_update_skill		= r2c_base + 8;
const short r2c_use_skill			= r2c_base + 9;

const short r2c_update_item			= r2c_base + 10;
const short r2c_add_item			= r2c_base + 11;	//地上捡起来或买过来
const short r2c_remove_item			= r2c_base + 12;
const short r2c_get_item_error		= r2c_base + 13;	//得到物体失败



const short r2c_update_attr			= r2c_base + 14;	//刷新属性
const short r2c_update_money		= r2c_base + 15;	//刷新钱
//const short r2c_update_effect_attr	= r2c_base + 16;	//刷新效果属性

const short r2c_effect_list			= r2c_base + 16;	//效果列表

const short r2c_teleport			= r2c_base + 17;	//瞬移
const short r2c_fight_win			= r2c_base + 18;	//战斗胜利
const short r2c_level_up			= r2c_base + 19;	//升级
const short r2c_update_task			= r2c_base + 20;	


const short r2c_attack				= r2c_base + 21;	//战斗
//交易
const short r2c_exchange_item		= r2c_base + 22;//玩家之间交换道具命令
//任务
const short r2c_task				= r2c_base + 23;//
//视频聊天CIM
const short r2c_cim					= r2c_base + 24;
//离开游戏
const short r2c_leave_game			= r2c_base + 25;

const short r2c_team				= r2c_base + 26;
//死亡
const short r2c_killed				= r2c_base + 27;

const short r2c_relive				= r2c_base + 28;

const short r2c_fight_hp			= r2c_base + 29;

const short r2c_look_play			= r2c_base + 30;

const short r2c_skill_hp			= r2c_base + 31;

const short r2c_who_die				= r2c_base + 32;

const short r2c_fight_miss			= r2c_base + 33;
const short r2c_skill_up			= r2c_base + 34;	//升级


const short r2c_update_state_attr	= r2c_base + 35;	//更新状态位
const short r2c_my_sell				= r2c_base + 36;	//摆摊
const short r2c_show_type			= r2c_base + 37;	//更新外观
const short r2c_change_scene		= r2c_base + 38;	//切换场景

const short r2c_runscript			= r2c_base + 39;	//

const short r2c_lifeskill			= r2c_base + 40;	// 生活技能通道

const short r2c_wuqi_attack			= r2c_base + 41;	// 攻城武器

const short r2c_vip					= r2c_base + 42;	// vi买卖通道

const short r2c_guozhan				= r2c_base + 43;	// 国战

const short r2c_mail_item			= r2c_base + 44;	// 邮寄功能专用通道
const short r2c_marry				= r2c_base + 45;

const short r2c_even				= r2c_base + 46;

const short r2c_guild_command		= r2c_base + 87;	//
const short r2c_gm_command			= r2c_base + 88;	//
const short r2c_update_skill_gm		= r2c_base + 89;	// Update specified role's data, not player self
const short r2c_update_item_gm		= r2c_base + 90;
const short r2c_update_attr_gm		= r2c_base + 91;
const short r2c_update_task_gm		= r2c_base + 92;

const short l2c_login_server	= r2c_base + 100;
const short l2c_gm_command		= r2c_base + 101;
const short l2c_change_scene	= r2c_base + 102;
const short l2c_guild_command	= r2c_base + 103;
const short l2c_friend_command	= r2c_base + 104;
const short l2c_gm_command_client= r2c_base + 105;
const short l2c_apex_command	= r2c_base + 106;



const short r2c_icq_setfriendtype_result	= r2c_base + 500; // ???

/*公会和任务专用网络消息*/

const short r2c_union_base = r2c_base + 1000;
const short r2c_union_add_member = r2c_union_base + 1;




/* client send to region */
const short c2r_base				= 1000;
const short c2r_chenmi				= c2r_base+c2r_base+1;
const short r2c_chenmi				= c2r_chenmi;
const short c2r_login				= c2r_base + 1;
const short c2r_chat				= c2r_base + 2;
const short c2r_walk_to			    = c2r_base + 3;
const short c2r_use_skill			= c2r_base + 4;
const short c2r_attack				= c2r_base + 5;
const short c2r_move_item			= c2r_base + 6;
const short c2r_drop_item			= c2r_base + 7;
const short c2r_get_item			= c2r_base + 8;
const short c2r_run_script			= c2r_base + 9;
const short c2r_use_item			= c2r_base + 10;

const short c2r_role_state   		= c2r_base + 11;//设置状态位//包括宠物状态

const short c2r_my_sell   			= c2r_base + 12;//摆摊

//const short c2r_chat_info			= c2r_base + 11;//查看道具信息//聊天的特殊信息

const short c2r_pet_command	  		= c2r_base + 13;//宠物命令

//交易
const short c2r_exchange_item		= c2r_base + 15;//玩家之间交换道具命令
//商店
const short c2r_shop_item			= c2r_base + 16;//商店道具命令
//任务
const short c2r_task				= c2r_base + 17;//任务

//视频聊天CIM
const short c2r_cim					= c2r_base + 18;
//复活
const short c2r_relive				= c2r_base + 19;


//离开游戏
const short c2r_leave_game			= c2r_base + 21;

//团队作用
const short c2r_team				= c2r_base + 22;

const short c2r_look_play			= c2r_base + 23;

const short c2r_join_sys			= c2r_base + 24;//合成系统命领。服务器的捡到命令
//娱乐中心
//const short c2r_yule_center			= c2r_base + 32;
const short c2r_lifeskill			= c2r_base + 25;	// 生活技能通道

const short c2r_wuqi_attack			= c2r_base + 26;	// 攻城武器

const short c2r_juqiattack			= c2r_base + 27;

const short c2r_mail_item			= c2r_base + 28;	//邮寄道具专用通道

const short c2r_marry				= c2r_base + 29;
const short c2r_rank				= c2r_base + 30;

//两个作用一样，只是区分一下
const short c2r_gm_command			= c2r_base + 88;
const short c2l_gm_command			= c2r_base + 89;
const short c2l_friend_command		= c2r_base + 90;
const short c2l_guild_command		= c2r_base + 91;
const short c2r_guild_command		= c2r_base + 92;
const short c2l_apex_command		= c2r_base + 93;
const short c2l_leave_game			= c2r_base + 94;

const short c2l_login_server		= c2r_base + 100; // ???
const short c2l_house				= c2r_base + 101; // 进入房子
const short c2l_even				= c2r_base + 102; // 一些特殊的事件
const short c2l_neweven				= c2r_base + 103; // 一些特殊的事件
const short c2l_rank				= c2r_base + 104;

const short c2r_use_fight_item		= c2r_base+122 ;//对对象使用道具

const short c2l_script				= c2r_base + 200; // 活动的事件
/* scene send to login */
const short s2l_base				= 2000;
const short s2l_login_scene			= s2l_base + 1;
const short s2l_check_login			= s2l_base + 2;//请求检验登入
const short s2l_updata_attr			= s2l_base + 3;//更新数据库信息
const short s2l_change_secene		= s2l_base + 4;//切换场景
const short s2l_leave_game			= s2l_base + 5;//离开游戏
const short s2l_even				= s2l_base + 6;//游戏事件

const short s2l_gm_command			= s2l_base + 10;
const short s2l_guild_command		= s2l_base + 11;

const short s2l_house				= s2l_base + 12;
const short s2l_rank				= s2l_base + 13;

/* login send to scene */
const short l2s_base				= 2000;
const short l2s_login_scene			= l2s_base + 1;
const short l2s_check_login			= l2s_base + 2;
const short l2c_chat				= l2s_base + 3;
const short l2s_even				= l2s_base + 4;
const short l2c_even				= l2s_base + 5;

const short l2s_gm_command			= l2s_base + 10;
const short l2s_guild_command		= l2s_base + 11;
const short l2s_rank_command		= l2s_base + 12;

const short l2c_house				= l2s_base + 21;
const short l2s_house				= l2s_base + 22;
const short l2c_neweven				= l2s_base + 23;

const short l2s_script				= l2s_base + 200; // 活动的事件

const short r2c_exp_rate =r2c_base+300;//add by coke 20090303
/*
const short r2c_icq_setfriendtype	= c2r_base + 500;//加好友，黑名单，删除
const short r2c_icq_loadfriendtype	= c2r_base + 501;//下载好友
const short c2r_icq_add	= c2r_base + 502;//加好友
const short r2c_icq_add	= c2r_base + 503;//加好友
const short c2r_icq_agree	= c2r_base + 504;//同意

const short c2r_icq_message	= c2r_base + 505;//发送的信息
const short r2c_icq_snapshot_up	= c2r_base + 506;//发送监测信息
const short r2c_icq_snapshot_down	= c2r_base + 507;//发送监测信息
const short c2r_icq_delete	= c2r_base + 508;//发送删除信息

const short c2r_icq_system	= c2r_base + 509;//系统命令信息

const short r2c_icq_leavegame	= c2r_base + 510;//系统命令信息

const short c2r_union_base = c2r_base + 1000;
const short c2r_union_update_union = c2r_union_base + 1; //向服务器请求更新公会信息
*/
const short MAX_ROLE_COUNT=3;//角色最大数
const short LOGIN_READ_INFO=4;//人物等入信息读取数

const short NAME_LENGH_MIN=4;
const short NAME_LENGH_MAX=16;

const short PWD_LENGH_MIN=6;
const short PWD_LENGH_MAX=16;

const short ROLE_TYPE_MAX=8;//暂时类型的最大数组
const short ROLE_TYPE_BEGIN_ID=1001;

const int CONST_HAIR_START[ROLE_TYPE_MAX] = {150, 950, 350, 1150, 550, 1350, 750, 1550};
const int CONST_HAIR_COUNT[ROLE_TYPE_MAX] = {11, 11, 11, 11, 11, 11, 11, 11};



//GM权利
const char GM_NULL		= 0;//无权利
const char GM_MIN		= 1;	// 最低权利
const char GM_MAX		= 10;	// 最高权限
const char GM_AGENT		= 4;

const char GM_REQUEST_OK				= 0;
const char GM_REQUEST_FAILED			= -1;
const char GM_REQUEST_DATABASE_ERROR	= -2;
const char GM_REQUEST_PLAYER_OFFLINE	= -3;
const char GM_REQUEST_PLAYER_NOTEXIST	= -4;
const char GM_REQUEST_NOT_DEFINED		= -5;

const char HIT_MISS		= 0;			// 没打中
const char HIT_DAMAGE	= 1;			// 正常伤害
const char HIT_DOUBLE	= 2;			// 双倍打击
const char HIT_DEAD		= 3;			// 是对方致死
const char HIT_SKILL_DOUBLE = 4;		// 技能双倍打击
const char HIT_SKILL_MISS	= 5;		// 技能没打中
const char HIT_SKILL_STATE	= 6;		// 技能正常伤害带状态
const char HIT_SKILL_DOUBLE_STATE = 7;	// 技能双倍打击并带状态
const char HIT_SKILL_GOOD	= 8;		// 技能加血
const char HIT_SKILL_HITTOO	= 9;		// 技能双连击
const char HIT_SKILL_MISSSTATE	= 10;		// 技能状态没打中

const short GM_COMMAND_CLOSE_SERVER		= 1;	//关闭服务器
const short GM_COMMAND_PUT_CREATURE		= 2;	//在地图上放置怪物
const short GM_COMMAND_KILL_CREATURE	= 3;
const short GM_COMMAND_DB_ADDRESS		= 4;
const short GM_COMMAND_CLIENT_TEST		= 5;
const short GM_COMMAND_CLIENT_TEST_RES	= 6;
const short GM_COMMAND_CLIENT_TEST_RES2	= 7;
const short GM_COMMAND_WAIGUA_KICKOUT	= 8;	//add by coke 踢外挂
const short GM_COMMAND_WAIGUA_COUNT		= 9;
const short GM_COMMAND_WAIGUA_TEST		= 10;

const short GM_COMMAND_CLIENT_TEST0		= 23;
const short GM_COMMAND_CLIENT_TEST1		= 11;
const short GM_COMMAND_CLIENT_TEST2		= 37;
const short GM_COMMAND_CLIENT_TEST3		= 39;
const short GM_COMMAND_CLIENT_TEST4		= 55;
const short GM_COMMAND_CLIENT_TEST5		= 93;
const short GM_COMMAND_CLIENT_TEST6		= 114;
const short GM_COMMAND_CLIENT_TEST7		= 220;
const short GM_COMMAND_CLIENT_TEST8		= 319;
const short GM_COMMAND_CLIENT_TEST9		= 402;

const short GM_COMMAND_ACCOUNT_BASE = 10;
const short GM_COMMAND_ACCOUNT_INFO_GET			= GM_COMMAND_ACCOUNT_BASE+1;	//通过帐号得到相关信息
const short GM_COMMAND_ACCOUNT_PASSWORD_RESET	= GM_COMMAND_ACCOUNT_BASE+2;	//add by coke 改账号密码该功能已取消
const short GM_COMMAND_ACCOUNT_BLOCK			= GM_COMMAND_ACCOUNT_BASE+3;	//add by coke 根据账号ID封账号
const short GM_COMMAND_ACCOUNT_UNBLOCK			= GM_COMMAND_ACCOUNT_BASE+4;	//add by coke 根据账号ID解封账号
const short GM_COMMAND_ACCOUNT_GET_ROLE			= GM_COMMAND_ACCOUNT_BASE+5;	//add by coke 通过角色获取账号信息
const short GM_COMMAND_ACCOUNT_AUTHORITY		= GM_COMMAND_ACCOUNT_BASE+6;
const short GM_COMMAND_ACCOUNT_ROLE_QUERY		= GM_COMMAND_ACCOUNT_BASE+7;	//add by coke 根据角色名查基本信息
const short GM_COMMAND_ACCOUNT_RESUME			= GM_COMMAND_ACCOUNT_BASE+8;	//add by coke 角色恢复
const short GM_COMMAND_ACCOUNT_KICK				= GM_COMMAND_ACCOUNT_BASE+9;	//add by coke 通过玩家名踢玩家

const short GM_COMMAND_PLAYER_INFO_GET			= GM_COMMAND_ACCOUNT_BASE+10;	//add by coke 根据ID获取信息
const short GM_COMMAND_PLAYER_KICK_OFFLINE		= GM_COMMAND_ACCOUNT_BASE+11;	//add by coke 根据角色ID踢角色
const short GM_COMMAND_PLAYER_TELEPORT_TOWN		= GM_COMMAND_ACCOUNT_BASE+12;	//add by coke 传送玩家到指定地点
const short GM_COMMAND_PLAYER_ID_GET			= GM_COMMAND_ACCOUNT_BASE+13;	//add by coke 根据角色名获取角色ID
const short GM_COMMAND_PLAYER_MODIFY_ATTRI		= GM_COMMAND_ACCOUNT_BASE+14;
const short GM_COMMAND_PLAYER_EQUIP_ITEM_DEL	= GM_COMMAND_ACCOUNT_BASE+15;
const short GM_COMMAND_PLAYER_EQUIP_ITEM_ADD	= GM_COMMAND_ACCOUNT_BASE+16;
const short GM_COMMAND_PLAYER_PACKAGE_ITEM_DEL	= GM_COMMAND_ACCOUNT_BASE+17;	//add by coke 删除玩家物品
const short GM_COMMAND_PLAYER_PACKAGE_ITEM_ADD	= GM_COMMAND_ACCOUNT_BASE+18;
const short GM_COMMAND_PLAYER_MODIFY_STATE_ATTRI= GM_COMMAND_ACCOUNT_BASE+19;	//add by coke SetAttr
const short GM_COMMAND_PLAYER_INVINCIBILITY		= GM_COMMAND_ACCOUNT_BASE+20;	//add by coke 无敌
const short GM_COMMAND_PLAYER_TELEPORT			= GM_COMMAND_ACCOUNT_BASE+21;	//add by coke 传送玩家到指定地点
const short GM_COMMAND_PLAYER_TELEPORT_TOWN_GAME= GM_COMMAND_ACCOUNT_BASE+22;	//add by coke 传送玩家到指定地点
const short GM_COMMAND_PLAYER_KICK_OFFLINE_GAME	= GM_COMMAND_ACCOUNT_BASE+23;	//add by coke 根据ID踢人
const short GM_COMMAND_PLAYER_KICK_OFFLINE_NAME	= GM_COMMAND_ACCOUNT_BASE+24;	// Kick off a player from login server by role name
const short GM_COMMAND_PLAYER_ID_GET_TELEPORT	= GM_COMMAND_ACCOUNT_BASE+25;
const short GM_COMMAND_PLAYER_RESET_STORE_PASSW	= GM_COMMAND_ACCOUNT_BASE+26;	//add by coke 修改仓库密码

const short GM_COMMAND_BULLETIN_ADD		   = GM_COMMAND_ACCOUNT_BASE+29;		//add by coke 添加公告
const short GM_COMMAND_BULLETIN_DEL		   = GM_COMMAND_ACCOUNT_BASE+30;		//add by coke 删除公告
const short GM_COMMAND_BULLETIN_UPDATE	   = GM_COMMAND_ACCOUNT_BASE+31;		//add by coke 发公告
const short GM_COMMAND_BULLETIN_DELETEALL  = GM_COMMAND_ACCOUNT_BASE+32;		//add by coke 删除所有公告

const short GM_COMMAND_CHAT_PLAYER2GM		= GM_COMMAND_ACCOUNT_BASE+40;
const short GM_COMMAND_CHAT_GM2PLAYER		= GM_COMMAND_ACCOUNT_BASE+41;		//add by coke GM对玩家说
const short GM_COMMAND_CHAT_MONITOR_REQ		= GM_COMMAND_ACCOUNT_BASE+42;		//add by coke GM监听
const short GM_COMMAND_CHAT_MONITOR_CANCEL	= GM_COMMAND_ACCOUNT_BASE+43;		//add by coke GM取消监听
const short GM_COMMAND_CHAT_MONITOR_MSG		= GM_COMMAND_ACCOUNT_BASE+44;
const short GM_COMMAND_CHAT_CRY				= GM_COMMAND_ACCOUNT_BASE+45;
const short GM_COMMAND_CHAT_FORBID			= GM_COMMAND_ACCOUNT_BASE+46;		//add by coke 通过角色ID禁言
const short GM_COMMAND_CHAT_FORBID_NAME		= GM_COMMAND_ACCOUNT_BASE+47;		//add by coke 通过角色名禁言

const short GM_COMMAND_ONLINE_NUM		= GM_COMMAND_ACCOUNT_BASE+50;
const short GM_COMMAND_TELEPORT			= GM_COMMAND_ACCOUNT_BASE+51;		//add by coke 瞬移
const short GM_COMMAND_TELEPORT_TOWN	= GM_COMMAND_ACCOUNT_BASE+52;		//add by coke 传送
const short GM_COMMAND_TELEPORT_2_PLAYER	= GM_COMMAND_ACCOUNT_BASE+53;	//add by coke GM传送到玩家身边
const short GM_COMMAND_PLAYER_2_GM			= GM_COMMAND_ACCOUNT_BASE+54;	//add by coke GM拉玩家

const short GM_COMMAND_ACTION_LOG	= GM_COMMAND_ACCOUNT_BASE+60;

const short GM_COMMAND_STARTSERVER	= GM_COMMAND_ACCOUNT_BASE+61;

const short GM_COMMAND_SET_EXPRATE			=GM_COMMAND_ACCOUNT_BASE+63;	//add by coke 20090225修改经验倍数

const short GM_COMMAND_CHAT_RESET_USER_PWD	=GM_COMMAND_ACCOUNT_BASE+70;	//add by coke 20090720修改玩家帐号密码
const short GM_COMMAND_CHAT_RESET_USER_JZ	=GM_COMMAND_ACCOUNT_BASE+71;	//add by coke 20090720清空玩家矩阵
const short GM_COMMAND_CHAT_RESET_ROLE_CK	=GM_COMMAND_ACCOUNT_BASE+72;	//add by coke 20090720修改角色仓库密码
const short GM_COMMAND_CHAT_SEARCH_ITEM		=GM_COMMAND_ACCOUNT_BASE+73;	//add by coke 20090720查道具表
const short GM_COMMAND_CHAT_CLEAR_MAC		=GM_COMMAND_ACCOUNT_BASE+76;	//add by coke 20090728清空MAC地址

// Friend
const char FRIEND_REQUEST_OK			= 0;
const char FRIEND_REQUEST_NOT_EXIST		= -1;
const char FRIEND_REQUEST_ALREADY_EXIST = -2;
const char FRIEND_REQUEST_DATABASE_ERROR= -3;
const char FRIEND_REQUEST_INVLID_PARAM	= -4;
const char FRIEND_REQUEST_NOT_AVAIBLE	= -5;		// 玩家的请求因为级别或别的不符合要求被拒绝
const char FRIEND_REQUEST_OFFLINE		= -6;
const char FRIEND_REQUEST_FULL			= -7;
const char FRIEND_REQUEST_FAILED		= -8;
const char FRIEND_REQUEST_BUSY			= -9;		// The object is in the waring state
const char FRIEND_REQUEST_EMPTY			= -10;		// Only be used in server
// sammy--
const char FRIEND_REQUEST_NOENOUGHITEM	= -11;		// 没有嗜血石  
const char FRIEND_REQUEST_NOENOUGHMONEY	= -12;		// 战争资金<100W/ 
// --sammy

const char FRIEND_REQUEST_WAR_SELF_WAR		= -20;
const char FRIEND_REQUEST_WAR_SELF_CREATE	= -21;
const char FRIEND_REQUEST_WAR_SELF_PROTECT	= -22;
const char FRIEND_REQUEST_WAR_TARGET_WAR	= -25;
const char FRIEND_REQUEST_WAR_TARGET_CREATE	= -26;
const char FRIEND_REQUEST_WAR_TARGET_PROTECT= -27;

const char FRIEND_STATE_ONLINE	= 0;
const char FRIEND_STATE_OFFLINE = 1;
const char FRIEND_STATE_LEAVE = 2;
const char FRIEND_STATE_REGAME = 3;

const char FRIEND_COMMAND_ADD			= 10;
const char FRIEND_COMMAND_DELETE		= 11;
const char FRIEND_COMMAND_GET_LIST		= 12;
const char FRIEND_COMMAND_STATE_CHANGE	= 13;
const char FRIEND_COMMAND_GET_INFO      = 14;
const char FRIEND_COMMAND_CHANGE_RELATION = 15;
const char FRIEND_COMMAND_ADD_RES		= 16;

// Rank
const char RANK_COMMAND_HEIGHT_UPDATE		= 10;
const char RANK_COMMAND_TAX_RATIO_REQ		= 11;
const char RANK_COMMAND_TAX_RATIO_CHANGE	= 12;
const char RANK_COMMAND_TAX_VALUE_REQ		= 13;
const char RANK_COMMAND_TAX_ADD				= 14;
const char RANK_COMMAND_TAX_GET				= 16;
const char RANK_COMMAND_RORBID_REQ			= 17;
const char RANK_COMMAND_RORBID_BY			= 18;
const char RANK_COMMAND_TAX                 = 65;   //官职系统的税收
const char RANK_COMMAND_PLAYERLEVEL         = 66;    //官职系统获取玩家等级排名
const char RANK_COMMAND_PLAYERWEALTH        = 67;    //官职系统获取玩家财富排名
const char RANK_COMMAND_PLAYERGLORY         = 68;    //官职系统获取玩家荣誉排名
// Guild
// 招收,开除,公告,任命,敌对,宣战,同盟,捐献,仓库,查询,建造,生产,脱离, // 需要贡献
const char GUILD_ACTION_ZHAOSHOU	= 0;		// 招收
const char GUILD_ACTION_KAICHU		= 1;		// 开除
const char GUILD_ACTION_GONGGAO		= 2;		// 公告
const char GUILD_ACTION_RENMING		= 3;		// 任命
const char GUILD_ACTION_DIDUI		= 4;		// 敌对
const char GUILD_ACTION_XUANZHAN	= 5;		// 宣战
const char GUILD_ACTION_TONGMENG	= 6;		// 同盟
const char GUILD_ACTION_JUANXIAN	= 7;		// 捐献
const char GUILD_ACTION_CANGKU		= 8;		// 仓库
const char GUILD_ACTION_CHAXUN		= 9;		// 查询
const char GUILD_ACTION_JIANZHAO	= 10;		// 建造
const char GUILD_ACTION_SHENGCHAN	= 11;		// 生产
const char GUILD_ACTION_TUOLI		= 12;		// 脱离
const char GUILD_ACTION_NUM			= 13;		// 

// 会员,精英,战将,猛将,长老,护法,宣传,内务,制造,外交,副会长数,会长数,	// 包宽度,包高度
const char GUILD_AUTHORITY_NULL			= 0;		// Not a guild member
const char GUILD_AUTHORITY_HUIYUAN		= 1;
const char GUILD_AUTHORITY_JINGYING		= 2;
const char GUILD_AUTHORITY_ZHANJIANG	= 3;
const char GUILD_AUTHORITY_MENGJIANG	= 4;
const char GUILD_AUTHORITY_ZHANGLAO		= 5;
const char GUILD_AUTHORITY_HUFA			= 6;
const char GUILD_AUTHORITY_XUANCHUAN	= 7;
const char GUILD_AUTHORITY_NEIWU		= 8;
const char GUILD_AUTHORITY_ZHIZAO		= 9;
const char GUILD_AUTHORITY_WEIJIAO		= 10;
const char GUILD_AUTHORITY_FUHUIZHANG	= 11;
const char GUILD_AUTHORITY_HUIZHANG		= 12;
const char GUILD_AUTHORITY_NUM			= 13;

const char GUILD_STATE_AUTHEN_NOT	= 0;
const char GUILD_STATE_AUTHENED		= 1;

// sammy--
const char GUILD_DEVELOP_STATE_INFANCY	= 0;
const char GUILD_DEVELOP_STATE_GROWING	= 1;
const char GUILD_DEVELOP_STATE_MANHOOD	= 2;
const char GUILD_DEVELOP_STATE_BREAK	= 3;
// --sammy


enum {GUILD_ALLIES_MAX = 2};

const short GUILD_COMMAND_BASE				= 10;
const short GUILD_COMMAND_CREATE			= GUILD_COMMAND_BASE+1;
const short GUILD_COMMAND_DISMISS			= GUILD_COMMAND_BASE+2;
const short GUILD_COMMAND_MEMBER_LIST		= GUILD_COMMAND_BASE+3;
const short GUILD_COMMAND_MEMBER_INVITE		= GUILD_COMMAND_BASE+4;
const short GUILD_COMMAND_MEMBER_JOIN		= GUILD_COMMAND_BASE+5;
const short GUILD_COMMAND_MEMBER_LEAVE		= GUILD_COMMAND_BASE+6;
const short GUILD_COMMAND_MEMBER_LEAVE_SELF	= GUILD_COMMAND_BASE+7;
const short GUILD_COMMAND_MEMBER_ADD		= GUILD_COMMAND_BASE+8;
//const short GUILD_COMMAND_MEMBER_DEL		= GUILD_COMMAND_BASE+9;
const short GUILD_COMMAND_CREATE_TEST		= GUILD_COMMAND_BASE+10;
const short GUILD_COMMAND_BULLETIN_SET		= GUILD_COMMAND_BASE+11;
const short GUILD_COMMAND_MEMBER_JOIN_GM	= GUILD_COMMAND_BASE+12;
const short GUILD_COMMAND_INITIAL			= GUILD_COMMAND_BASE+13;
const short GUILD_COMMAND_PROTECT_UPDATE	= GUILD_COMMAND_BASE+14;

const short GUILD_COMMAND_MEMBER_KICKOUT	= GUILD_COMMAND_BASE+20;
const short GUILD_COMMAND_MEMBER_UPGRADE	= GUILD_COMMAND_BASE+21;
const short GUILD_COMMAND_MEMBER_DEGRADE	= GUILD_COMMAND_BASE+22;
const short GUILD_COMMAND_MEMBER_AUTHO_SET	= GUILD_COMMAND_BASE+23;
const short GUILD_COMMAND_MEMBER_STATE_CHANGE		= GUILD_COMMAND_BASE+24;
const short GUILD_COMMAND_MEMBER_PRESENT_CHANGE		= GUILD_COMMAND_BASE+25;
const short GUILD_COMMAND_MEMBER_CONTRIBUTE_CHANGE	= GUILD_COMMAND_BASE+26;

const short GUILD_COMMAND_CHAT			= GUILD_COMMAND_BASE+30;
const short GUILD_COMMAND_CHAT_OFFICER	= GUILD_COMMAND_BASE+31;

const short GUILD_COMMAND_AUTHEN_TEST	= GUILD_COMMAND_BASE+40;
const short GUILD_COMMAND_CHARGE_CHANGE	= GUILD_COMMAND_BASE+41;
const short GUILD_COMMAND_CHARGE_STATE	= GUILD_COMMAND_BASE+42;

// Guild store
const short GUILD_COMMAND_STORE_ITEM		= GUILD_COMMAND_BASE+50;
//const short GUILD_COMMAND_STORE_DEPOSITE	= GUILD_COMMAND_BASE+51;
//const short GUILD_COMMAND_STORE_FETCH		= GUILD_COMMAND_BASE+52;
const short GUILD_COMMAND_STORE_POSITION	= GUILD_COMMAND_BASE+54;
const short GUILD_COMMAND_STORE_REQUEST		= GUILD_COMMAND_BASE+55;
const short GUILD_COMMAND_STORE_LEFT		= GUILD_COMMAND_BASE+56;
const short GUILD_COMMAND_STORE_OUT			= GUILD_COMMAND_BASE+57;
const short GUILD_COMMAND_STORE_IN			= GUILD_COMMAND_BASE+58;

const short GUILD_COMMAND_RESOURCE_IN		= GUILD_COMMAND_BASE+80;
const short GUILD_COMMAND_RESOURCE_CHANGE	= GUILD_COMMAND_BASE+81;

const short GUILD_COMMAND_MSG_VALUE_CHANGE		  = GUILD_COMMAND_BASE+100;
const short GUILD_COMMAND_MSG_VALUE_CHANGE_SINGLE = GUILD_COMMAND_BASE+101;

const short GUILD_COMMAND_ALLY_REQ			= GUILD_COMMAND_BASE+120;
const short GUILD_COMMAND_ALLY_REQ_RES		= GUILD_COMMAND_BASE+121;
const short GUILD_COMMAND_ALLY_REPLY		= GUILD_COMMAND_BASE+122;
const short GUILD_COMMAND_ALLY_DISSOLUTION	= GUILD_COMMAND_BASE+123;
const short GUILD_COMMAND_ALLY_UPATE		= GUILD_COMMAND_BASE+124;

const short GM_COMMAND_GUILD_WAR_LIST		= GUILD_COMMAND_BASE+150;
const short GM_COMMAND_GUILD_WAR_DEC_LIST	= GUILD_COMMAND_BASE+151;

// GS used guild command
const short GUILD_COMMAND_NOTIFY_GS		= GUILD_COMMAND_BASE+200;
const short GUILD_COMMAND_STONE_CREATE	= GUILD_COMMAND_BASE+201;
const short GUILD_COMMAND_STONE_DELETE	= GUILD_COMMAND_BASE+202;
const short GUILD_COMMAND_STONE_INITIAL	= GUILD_COMMAND_BASE+203;
const short GUILD_COMMAND_NOTIFY_ROUND	= GUILD_COMMAND_BASE+204;
const short GUILD_COMMAND_BUILDING_INITIAL	= GUILD_COMMAND_BASE+205;
const short GUILD_COMMAND_BUILDING_NEW		= GUILD_COMMAND_BASE+206;	// Notify to GS
const short GUILD_COMMAND_BUILDING_REPAIR	= GUILD_COMMAND_BASE+207;	// Notify to GS

// Guild application
const short GUILD_APPLICATION_ALL_GUILD_REQ	= GUILD_COMMAND_BASE+300;	// Request all guild info
const short GUILD_APPLICATION_INITIAL		= GUILD_COMMAND_BASE+301;	// Request a guild's application
const short GUILD_APPLICATION_LEFT			= GUILD_COMMAND_BASE+302;	// The guild's officer stop get applications
const short GUILD_APPLICATION_REQ			= GUILD_COMMAND_BASE+303;
const short GUILD_APPLICATION_CONCENT		= GUILD_COMMAND_BASE+304;
const short GUILD_APPLICATION_REFUSE		= GUILD_COMMAND_BASE+305;
const short GUILD_APPLICATION_REQ_RES		= GUILD_COMMAND_BASE+306;

// Guild building
const short GUILD_COMMAND_CASTLE_COMEIN			   = GUILD_COMMAND_BASE+400;
const short GUILD_COMMAND_CASTLE_LEFT			   = GUILD_COMMAND_BASE+401;
const short GUILD_COMMAND_BUILDING_LEVEL_START	   = GUILD_COMMAND_BASE+402;
const short GUILD_COMMAND_BUILDING_LEVEL_END	   = GUILD_COMMAND_BASE+403;
const short GUILD_COMMAND_BUILDING_LEVEL_CANCEL	   = GUILD_COMMAND_BASE+404;
const short GUILD_COMMAND_BUILDING_LEVEL_DEGRADE   = GUILD_COMMAND_BASE+405;
// sammy--
const short GUILD_COMMAND_GUILD_GROWUP             = GUILD_COMMAND_BASE+406;
const short GUILD_COMMAND_ADD_GUILD_STONE          = GUILD_COMMAND_BASE+407;
const short GUILD_COMMAND_GUILD_MOVE               = GUILD_COMMAND_BASE+408;
const short GUILD_COMMAND_DELETE_GUILD             = GUILD_COMMAND_BASE+409;
// --sammy

const short GUILD_COMMAND_BUILDING_UPGRADE_EXP		= GUILD_COMMAND_BASE+410;
const short GUILD_COMMAND_BUILDING_UPGRADE_EXP_TEMP	= GUILD_COMMAND_BASE+411;


// sammy--
const short GUILD_COMMAND_GUILD_BAR_USE        		= GUILD_COMMAND_BASE+415;
const short GUILD_COMMAND_WAR_SELF_EVADE        	= GUILD_COMMAND_BASE+416;
const short GUILD_COMMAND_WAR_ENEMY_EVADE        	= GUILD_COMMAND_BASE+417;
const short GUILD_COMMAND_GUILD_REPAIR 		        = GUILD_COMMAND_BASE+418;
const short GUILD_COMMAND_GUILD_STATE_GROWING 		= GUILD_COMMAND_BASE+419;
const short GUILD_COMMAND_GUILD_STATE_BREAK 		= GUILD_COMMAND_BASE+496;
const short GUILD_COMMAND_ENEMY_STATE_BREAK 	        = GUILD_COMMAND_BASE+497;
// --sammy


const short GUILD_COMMAND_CREATURE_BUY		= GUILD_COMMAND_BASE+420;
const short GUILD_COMMAND_CREATURE_BORN		= GUILD_COMMAND_BASE+421;
const short GUILD_COMMAND_FORGESHOP_COMPOSE	= GUILD_COMMAND_BASE+440;
const short GUILD_COMMAND_FORGESHOP_BUY		= GUILD_COMMAND_BASE+441;

const short GUILD_COMMAND_WAR_DECLARE		= GUILD_COMMAND_BASE+480;
const short GUILD_COMMAND_WAR_DECLARE_RES	= GUILD_COMMAND_BASE+481;
const short GUILD_COMMAND_ENEMY_DECLARE		= GUILD_COMMAND_BASE+482;
const short GUILD_COMMAND_ENEMY_DECLARE_RES	= GUILD_COMMAND_BASE+483;
const short GUILD_COMMAND_WAR_CANCEL		= GUILD_COMMAND_BASE+484;	// 敌对状态
const short GUILD_COMMAND_WAR_WIN			= GUILD_COMMAND_BASE+485;	// 敌对状态
const short GUILD_COMMAND_WAR_MONEY_CONFIRM	= GUILD_COMMAND_BASE+490;
const short GUILD_COMMAND_WAR_MONEY_LOST	= GUILD_COMMAND_BASE+491;
const short GUILD_COMMAND_WAR_MONEY_GET		= GUILD_COMMAND_BASE+492;
const short GUILD_COMMAND_WAR_PROTECT		= GUILD_COMMAND_BASE+493;
const short GUILD_COMMAND_WINWAR_TROPHY		= GUILD_COMMAND_BASE+494;  // sammy


const short GUILD_COMMAND_INTOGUILD			= GUILD_COMMAND_BASE+501;//进入公会
const short GUILD_COMMAND_OUTGUILD			= GUILD_COMMAND_BASE+502;//离开公会
const short GUILD_COMMAND_UPDATA_ENEMY_SELF	= GUILD_COMMAND_BASE+503;//更新敌对公会
const short GUILD_COMMAND_UPDATA_ENEMY_ALLY	= GUILD_COMMAND_BASE+504;

const short GUILD_COMMAND_GS_CREATURE_ADD		= GUILD_COMMAND_BASE+550;	// 
const short GUILD_COMMAND_GS_CREATURE_DEAD		= GUILD_COMMAND_BASE+551;	// 
const short GUILD_COMMAND_GS_WAR_STATE			= GUILD_COMMAND_BASE+552;	// 敌对状态
const short GUILD_COMMAND_GS_WAR_END			= GUILD_COMMAND_BASE+553;	// 敌对状态
const short GUILD_COMMAND_GS_WAR_START			= GUILD_COMMAND_BASE+554;	// 敌对状态
const short GUILD_COMMAND_GS_WAR_END_LOGIN		= GUILD_COMMAND_BASE+555;	// 敌对状态

const short GUILD_COMMAND_SKILL_USED		= GUILD_COMMAND_BASE+570;	// 敌对状态


const int CONST_UNION_VALUE_COUNT = 4;	//公会变量的个数
const int CONST_UNION_BUILDING_COUNT = 10;
const int CONST_UNION_BUILDING_MAX_LEVEL = 3;

const int CONST_UNION_BUILDING_MAX_EXP = 10000;		//建筑经验最大值

// Guild building
const char GUILD_B_GUILD		= 0;		// 公会
const char GUILD_B_TAVERN		= 1;		// 酒馆		
const char GUILD_B_FORGESHOP	= 2;		// 铁匠铺
const char GUILD_B_STORE		= 3;		// 仓库
const char GUILD_B_FORT			= 4;		// 堡垒
const char GUILD_B_DEPOT		= 5;		// 补给站
const char GUILD_B_BARACKS		= 6;		// 兵营
const char GUILD_B_WONDER		= 7;		// 奇迹
const char GUILD_B_PARLIAMENT	= 8;		// 议会厅
const char GUILD_B_MAGICTOWER	= 9;		// 魔法塔
const char GUILD_B_NUM			= 10;		// 

// Resource
const char RESOURCE_MONEY		= 0;		// money....
const char RESOURCE_STONE		= 1;		// 石头
const char RESOURCE_WOOD		= 2;		// 木头
const char RESOURCE_SULFUR		= 3;		// 硫磺
const char RESOURCE_SILVER		= 4;		// 水银
const char RESOURCE_CRYSTAL		= 5;		// 水晶
const char RESOURCE_MAX			= 6;		//

const char GUILD_SOIDIER_TYPE_COUNT = 6;


//邮件系统 呵呵

const char MAIL_ITEM_SEND       = 0;		//发送邮件
const char MAIL_ITEM_GETLIST    = 1;		//取得我的邮件列表
const char MAIL_ITEM_GETMAIL    = 2;		//拿取一个邮件
const char MAIL_ITEM_DELMAIL	= 3;		//删除一个邮件	必须已经将道具拿走了才行
const char MAIL_ITEM_APPEND     = 4;		//玩家拿去一个邮件后，如果数据库里面还有 可以添加 
const char MAIL_ITEM_DETAIL     = 5;		//玩家看一个邮件 
const char MAIL_ITEM_GETITEM	= 6;		//拿走一个道具
const char MAIL_ITEM_DELETEMAIL = 7;
const char MAIL_ITEM_GETMONEY	= 8;		//取得钱
const char MAIL_ITEM_CLOSEMAIL  = 9;		//告诉服务器重新打开邮箱
//拍卖系统的消息
const char MAIL_PUBLICSELL_GETLIST  = 10;	//请求拍卖物品的列表
const char MAIL_PUBLICSELL_SELLITEM = 11;	//拍一个物品
const char MAIL_PUBLICSELL_BUYITEM  = 12;	//出价一个物品
const char MAIL_PUBLICSELL_BUYITEMONE = 13;	//一口价买
const char MAIL_PUBLICSELL_VIPBUY	= 14;	//VIP购买
const char MAIL_PUBLICSELL_MYITEMLIST = 15;	//我的VIP道具
const char MAIL_PUBLICSELL_GETBACK = 16;	//拿回我的拍卖物品

const char MAIL_NOTIFY_CHAR = 17;			//服务器向客户端发送一条 信息

const int MAX_PUBLICSELL_RESULT_COUNT = 10;	//一次最多20条 多了费劲

const char PUBLICSELL_ERROR_MONEY = 1;		//出价了但是钱不够
const char PUBLICSELL_ERROR_LOWPRICE = 2;	//出价低于现价
const char PUBLICSELL_ERROR_NOTFIND = 3;	//物品没有找到
const char PUBLICSELL_ERROR_OTHER = 4;		//其他错误
const char PUBLICSELL_ERROR_SELLMYFULL = 5;	//自己的东西太多了
const char PUBLICSELL_ERROR_SELLINDEXFULL = 6;	//index full

//拍卖系统 呵呵
const char PUBLICSELL_SEARCH_BYROLE = 0;	//按照拍卖人查询
const char PUBLICSELL_SEARCH_BYTYPE = 1;	//按照道具类型查询
const char PUBLICSELL_SEARCH_BYQLV  = 2;		//按照道具品质
const char PUBLICSELL_SEARCH_BYLEVEL = 3;	//按照道具使用等级
const char PUBLICSELL_SEARCH_BYTYPEID = 4;	//按照道具类型id查询

const char PUBLICSELL_TYPE_ALL = 0;
const char PUBLICSELL_TYPE_MY = 1;

const long MAIL_READ_PROTECT_TIME = 20000;	//读取邮件间隔

const int MAX_MAIL_COUNT = 10;				//个人最大读取邮件的数量




//结婚系统 呵呵

const char MARRY_REQUEST	= 1;		//结婚请求
const char MARRY_ALLOW		= 2;		//同意请求
const char MARRY_REFUSE		= 3;		//求婚被拒绝了

const char MARRY_SUCESS		= 4;		//谁和谁结婚成功
const char MARRY_FAIL		= 5;		//结婚失败了



const char MARRY_UPCHE		= 41;		//结婚上车
const char MARRY_DOWNCHE	= 42;		//结婚下车
const char MARRY_CHEWALK	= 43;		//结婚车上走路

const char MARRY_SONG_CAILI	= 44;		//结婚换彩礼
const char MARRY_HUAN_CAILI	= 45;		//结婚送彩礼

const char MARRY_CHANGE_SCENE	= 46;		//结婚切换场景

const char MARRY_CHECKOK		= 50;		//满足结婚前提
const char MARRY_NO_RING		= 51;		//没有结婚前提道具
const char MARRY_NO_LEVEL		= 52;		//
const char MARRY_NO_MONEY		= 53;		//
const char MARRY_MARRYED		= 54;		//已经有伴侣
const char MARRY_SEX_ERROR		= 55;		//性别相同
//const char MARRY_REFUSE		= 53;		//求婚被拒绝了

const char MARRY_PARAM_ERROR = -2;	//参数错误	
const char MARRY_NOTONLINE = -1;		//没有找到对象




	


/*道具出错的标志*/
const int COMBIN_ERROR_NOERROR = 0;		//没有出错
const int COMBIN_ERROR_NOERROR_EXP =  1;
const int COMBIN_ERROR_PRODUCTID_ERROR = 2; //要合成不在合成列表中的道具
const int COMBIN_ERROR_NOPEIFANG = 3;		//没有配方
const int COMBIN_ERROR_TABLE = 4;			//配方表有错误
const int COMBIN_ERROR_NOTPLAYER = 5;		//怪物要合成道具
const int COMBIN_ERROR_NOPACK = 6;			//没有包裹
const int COMBIN_ERROR_NOTENOUGH_RES = 7;	//没有足够的材料
const int COMBIN_ERROR_NOTENOUGH_SPACE = 8;	//没有足够的空格
const int COMBIN_ERROR_SKILL_NOTENOUGH = 9;
const int COMBIN_ERROR_ERROR_UNKNOW = 10;

const int FJ_NO_ERROR			= 0;		//分解成功
const int FJ_ERROR_NO_PACKET = 1;			//没有包包
const int FJ_ERROR_NOTFIND  = 2;			//没有道具
const int FJ_ERROR_CANFJ	= 3;			//不是可以分解的道具
const int FJ_ERROR_TABLE_ERROR = 4;			//分解表出错
const int FJ_ERROR_FULL			= 5;		//放不下了
const int FJ_ERROR_SHORTMONEY   = 6;		//钱不够
const int FJ_ERROR_TOOFASE = 7;				//分解的太快了


const int SP_ERROR_NOERROR = 0;
const int SP_ERROR_NOCHIP = 1;				//数据没有找到
const int SP_ERROR_SKILL = 2;				//技能不足
const int SP_ERROR_NOPACK = 3;				//没有包包
const int SP_ERROR_NOTARGET = 4;			//抚摸对象不存在
const int SP_ERROR_TARGETERROR = 5;			//不能抚摸对象
const int SP_ERROR_ATTRFULL = 6;			//属性满了
const int SP_ERROR_NORES = 7;				//没有抚摸材料
const int SP_ERROR_NOTENOUGHMONEY = 8;		//金钱不足
const int SP_ERROR_TABLEERROR = 9;			//服务器数据错误
const int SP_ERROR_NOSTONE = 10;			//没有石头

const int SP_ERROR_FAIL_PROTECTED = 11;
const int SP_ERROR_FAIL_NOPROTECTED = 12;
const int SP_ERROR_SUCCESS = 13;

const int SP_ERROR_EXT_STONE = 14;				//分解85特殊宝石

enum EPhyleType
{
	EPhyle_NULL				= 0,	    // 中立
	EPhyle_TIANCHAO			= 1,		//天朝
	EPhyle_DIGUO			= 2,		//帝国
	EPhyle_MOZU				= 3,		//魔族
	
	
	EPhyle_MAX				= 4,
	
};


const char INTO_HOUSE		= 1;			// 进入房子
const char LEAVE_HOUSE		= 2;			// 离开房子
const char ADD_FURNITURE	= 3;			// 添加家具
const char DELETE_FURNITURE = 4;			// 删除家具
const char MY_HOUSE_LIST	= 5;			//服务器返回我的房子列表		
const char HOUSE_GETHOUSE   = 6;			//租房子
const char HOUSE_CHANGEFLOOR = 7;			//更换地板
const char HOUSE_PUTFURNITURE = 8;			//放置家具
const char HOUSE_MOVEFURNITURE = 9;			//移位置
const char HOUSE_GETFURBACK = 10;			//把家具

const char HOUSE_CANIIN = 11;				//检查是否可以进去
const char HOUSE_UPDATE_FUR = 12;			//更新家具用
const char HOUSE_USE_FUR = 13;				//使用家具
const char HOUSE_GETOLD_FUR = 14;			//读取家具列表
const char HOUSE_GETOLDFURBACK = 15;		//取回家具
const char WARMANAGE_SEND = 16;				//国战命令
const char HOUSE_BACKHOME = 17;
const char FRIEND_GOTO_QUERY = 18;			//飞到朋友那里去 问MAPSERVER要坐标
const char FRIEND_GOTO = 19;			
const char FRIEND_GOTO_ERROR = 20;
const char FRIEND_SUMMER = 21;				//召唤朋友过来
const char FRIEND_SUMMER_REQ = 22;			//询问朋友是否愿意飞过来
const char FRIEND_SUMMER_ERROR = 23;
const char FRIEND_SUMMER_REFUSE = 24;		//被拒绝了
const char FRIEND_SUMMERGOTO = 25;
const char FRIEND_SUMMERGOTO_QUERY = 26;
const char MSGFROM_MAPSERVER = 27;			//MAP SERVER 发来的信息
const char MAPSERVER_EVENT = 28;			//有人欺骗 MAP_SERVER



const char FUR_UPDATE_TYPE_ADD = 1;
const char FUR_UPDATE_TYPE_DEL = 2;
const char FUR_UPDATE_TYPE_MOV = 3;
const char FUR_UPDATE_TYPE_LOCK = 4;	//关门
const char FUR_UPDATE_TYPE_OPEN = 5;

const char L2R_HOUSE_GET_HOUSE = 1;			//LOGIN SERVER向MAP_SERVER发送的 购买房屋的 请求
const char L2R_HOUSE_PUTFUR = 2;			//放家具 呵呵
const char L2R_HOUSE_GETFUR = 3;			//把家具放回包里
const char L2R_HOUSE_USEFUR = 4;			//使用家具
const char L2R_HOUSE_GETOLDFUR = 5;
const char L2R_HOUSE_WORLDEDITSAY = 6;		//世界纳巴
const char L2R_HOUSE_BACKHOME = 7;			//回家

const char HOUSECANIN_EMPTY = 0;			//空房子
const char HOUSECANIN_OTHER = 1;			//其他人的房间不能进入
const char HOUSECANIN_MY = 2;				//我的房间
const char HOUSECANIN_PEIOU = 3;			//配偶
const char HOUSECANIN_GUILD = 4;			//公会会员
const char HOUSECANIN_FRIEND = 5;			//好朋友的房子


const long HOUSE_GET_TIME = 1000;//3600*24*3;		//租房子的时间 单位秒


const char HOUSE_ERROR_GET_NOTEMPTY = 1;	//房子不是空的不能组
const char HOUSE_ERROR_GET_GOLDERROR = 2;	//白金币不足
const char HOUSE_ERROR_GET_MONEYERROR = 3;	//游戏币不足
const char HOUSE_ERROR_GET_DATABASE = 4;	//数据库错误
const char HOUSE_ERROR_GET_NOHOUSE = 5;		//房子不存在
const char HOUSE_ERROR_GET_PROTECTED = 6;	//房子被保护起来了
const char HOUSE_ERROR_GET_OWNERERROR = 7;	//主人错误
const char HOUSE_ERROR_GET_BAGFULL = 8;		//包包满了无法回收道具
const char HOUSE_ERROR_GET_NOHOST = 9;		//主人找不到
const char HOUSE_ERROR_GET_BAGERROR = 10;	//包包不见了
const char HOUSE_ERROR_FUR_COLDDOWN = 11;	//家具在colddown
const char HOUSE_ERROR_FUR_NOTFIND = 12;	//家具找不到
const char HOUSE_ERROR_FUR_END = 13;		//家具耐久为0


const char HOUSE_LUA_EXEC_HOST = 0;	//主人使用家具
const char HOUSE_LUA_EXEC_LOVER = 1; //配偶使用家具
const char HOUSE_LUA_EXEC_FRIEND = 2; //朋友使用家具
const char HOUSE_LUA_EXEC_GUILD = 3;	//同工会的使用家具
const char HOUSE_LUA_EXEC_ENEMY = 4;	//敌人使用家具
const char HOUSE_LUA_EXEC_OTHER = 127;	//其他人


const int HOUSE_FUR_MAX_LEVEL1 = 10;
const int HOUSE_FUR_MAX_LEVEL2 = 20;
const int HOUSE_FUR_MAX_LEVEL3 = 30;
const int HOUSE_FUR_MAX_LEVEL4 = 40; 


const char PK_STATE_NONE = 0;				//没有PK状态
const char PK_STATE_DEFEND = 1;				//被动PK
const char PK_STATE_NORMAL		= 2;		//只是PK状态 
const char PK_STATE_ATTACKED	= 3;		//主动PK	杀这种人 不增加罪恶	//状态保留


const long PK_TIME = 200000;				//可以被杀的状态保留时间
const long PK_NOKILL_TIME = 100000;			//玩玩的pk保留时间


const int IS_PK_TRUE_NOPK = 0; //不是pk
const int IS_PK_KILL_PK	= 1;	//有罪恶值得PK
const int IS_PK_NOKILL_PK = 2;	//自由PK	


//-----------gamelog-----------//
const short GAMELOG_ALL				= 0;	// 全部
const short GAMELOG_GM				= 1;	//gm耍属性
const short GAMELOG_BUY				= 2;	//买
const short GAMELOG_SELL			= 3;	//卖
const short GAMELOG_EXCHANGE		= 4;	//交易
const short GAMELOG_EXCHANGE_MONEY	= 5;	//交易金钱显示是前面的id给后面的id
const short GAMELOG_EXCHANGE_ERROR	= 6;	//交换道具失败,一般不会出现
const short GAMELOG_DROP			= 7;	//丢弃
const short GAMELOG_DEADDROP		= 8;	//死亡掉落
const short GAMELOG_RANFA			= 9;	//染发
const short GAMELOG_XISHOUSTONE		= 10;	//吸收属性石
const short GAMELOG_CHENGZHANG_START		= 11;	//开始成长道具，
const short GAMELOG_CHENGZHANG				= 12;	//成长道具，
const short GAMELOG_CHENGZHANG_ENDOK		= 13;	//完成成长道具，成功
const short GAMELOG_CHENGZHANG_ENDSHIBAI	= 14;	//完成成长道具，失败
const short GAMELOG_CHENGZHANG_ENDXIAOSHI	= 15;	//完成成长道具，失败并消失
const short GAMELOG_UNIONDEAD	= 16;	//公会被打败了,myid被creid打败
const short GAMELOG_FENJIE_ITEM = 17;	//道具分解
const short GAMELOG_FUMO_ITEM_SUCCESS_PROTECTED = 18;		//道具附魔成功 并消耗了保护石
const short GAMELOG_FUMO_ITEM_SUCCESS_NOPROTECTED = 19;		//道具附魔成功 没有消耗了保护石
const short GAMELOG_FUMO_ITEM_FAILPROTECTED = 20;		//道具附魔失败 消耗了保护石 属性保护
const short GAMELOG_FUMO_ITEM_FAILNOPROTECTED = 21;		//道具附魔失败 没有保护石 属性没有了
const short GAMELOG_COMBIN_ITEM = 22;	//道具合成
const short GAMELOG_GUILD = 23;	//公会日志
const short GAMELOG_EXCHANGE_CHEAT	= 24;			//出现了骗子
const short GAMELOG_OLDFER_GETBACK = 25;			//拿回旧家具
const short GAMELOG_GETFUR_BACK = 26;				//拿回家具
const short GAMELOG_GETITEM = 27;					//地上拿起来
const short GAMELOG_SCRIPTITEM = 28;				//脚本添加
const short GAMELOG_MAIL_TAKEMONEY = 29;			//拿取邮件中的钱
const short GAMELOG_MAIL_TAKEITEM = 30;				//拿取邮件中的道具
const short GAMELOG_MAIL_SENDMONEY = 31;			//邮寄钱
const short GAMELOG_MAIL_SENDITEM = 32;				//邮寄道具
const short GAMELOG_MAIL_DELETEMAIL = 33;			//删除了邮件
const short GAMELOG_MAIL_YUEGUANG = 34;				//月光宝盒
const short GAMELOG_MAIL_YUEGUANG_RESEED = 35;				//月光宝盒
const short GAMELOG_PUBLICSELL_SELL = 36;			//拍卖
const short GAMELOG_PETEGG_UP = 37;			//宠物蛋升级
const short GAMELOG_FANGJU_UP = 38;			//强化防具
const short GAMELOG_LIFE_UP	  = 39;			//增加燃点
const short GAMELOG_GET_LIPIN	  = 40;			//拿礼品
const short GAMELOG_JIONTIANSHEN  = 41;			//合成天神
const short GAMELOG_SCRIPT	= 43;	//脚本log
const short GAMELOG_STAR_UP = 44;			//升星
const short GAMELOG_BREAK_SOUL = 45;			//灵魂分解
const short GAMELOG_RESORT_OTHER_ATTR = 46;		//额外属性重列f
const short GAMELOG_A_to_B = 47;		//物品AtoB
const short GAMELOG_VIPBUY		= 100;	//vip买卖东西
const short GAMELOG_VIPBUYCOUNT	= 101;	//vip消费点
const short GAMELOG_VIPBUYCOUNT_BUYITEM	= 102;	//vip消费点买东西
const short GAMELOG_CHENGZHANG_SHENQI_START			= 103;	//开始成长道具，神器相关
const short GAMELOG_CHENGZHANG_SHENQI				= 104;	//成长道具，
const short GAMELOG_CHENGZHANG_SHENQI_ENDOK			= 105;	//完成成长道具，成功
const short GAMELOG_CHENGZHANG_SHENQI_ENDSHIBAI		= 106;	//完成成长道具，失败
const short GAMELOG_CHENGZHANG_SHENQI_ENDXIAOSHI	= 107;	//完成成长道具，失败并消失
//对象操作值来定义成功还是失败
const char VIPBUY_OK			= 1;	//成功购买VIP成功
const char VIPBUY_ERROR_DB		= 2;	//更新数据库失败
const char VIPBUY_ERROR_GETITEM		= 3;	//生成道具失败
const char VIPBUY_ERROR_NOMENOY		= 4;	//钱不足
const char VIPBUY_ERROR_ADDITEM		= 5;	//加入道具失败

const char VIPBUY_UPDATA_MENOY		= 10;	//更新钱
const char VIPBUY_UPDATA_VIPBUYCOUNT = 11; //更新消费点


//---------s2l--even----//
const char CSL_GOMYROUND		= 1;	//到玩家身边
const char CSL_KICKOUT			= 2;	//踢掉玩家
const char CSL_USEMENOY			= 3;	//花钱
const char CSL_USEITEM			= 4;	//用道具
const char CSL_NABA				= 5;	//大喇叭 呵呵
const char CSL_STOP				= 6;	//stop
const char CSL_NABA_SYSTEM		= 7;	//系统专用喇叭
const char CSL_CHANGETYPE		= 8;	//变性

const char CSL_USER_CHENGMI_TISHI		= 17;	//提示

const char CSL_DROPITEM			= 21;	//丢失道具保护


const char CSL_CHECK_MIBAO			= 30;	//请求密宝//客户段输入密码
const char CSL_CHECK_MIBAO_OK		= 31;	//请求密宝//客户段输入密码
const char CSL_CHECK_MIBAO_ERROR	= 32;	//请求密宝//客户段输入密码
const char CSL_CHECK_MIBAO_GM		= 33;	//gm请求密宝//客户段输入密码
const char CSL_CHECK_MATRIX			= 34;	//矩阵卡输入//客户段输入密码
const char CSL_CHECK_MATRIX_ERROR	= 35;	//矩阵卡输入//客户段输入密码

const char CSL_REAL_GET_PASSWORD	= 36;	//获取real平台的帐号信息，做为备份

const char CSL_WENDAN_START		= 41;	//问答开始
const char CSL_WENDAN_INFO		= 42;	//问答信息
const char CSL_WENDAN_RIGHT		= 43;	//问答正确
const char CSL_WENDAN_ERROR		= 44;	//问答错误
const char CSL_WENDAN_END		= 45;	//问答结束
const char CSL_WENDAN_HUIDA		= 46;	//问答-客户端回答
const char CSL_WENDAN_MAXNUM	= 47;	//问答-超过一天的次数了
  
const char CSL_SYS_WENDAN_REQUIRE_END=48;  //玩家要求退出系统问答






const char CSL_SYS_WENDAN_READY     =91;  //系统问答向所有玩家发送准备信息
const char CSL_SYS_WENDAN_START		= 92;	//系统问答开始
const char CSL_SYS_WENDAN_INFO		= 93;	//系统问答信息
const char CSL_SYS_WENDAN_RIGHT		= 94;	//系统问答正确
const char CSL_SYS_WENDAN_WRONG		= 95;	//系统问答错误
const char CSL_SYS_WENDAN_END		= 96;	//系统问答结束
const char CSL_SYS_WENDAN_HUIDA		= 97;	//系统问答-客户端回答
const char CSL_SYS_WENDAN_MAXNUM	= 98;	//系统问答-超过一天的次数了
const char CSL_SYS_WENDAN_ENDBACK	= 99;	//系统问答结束

const char CSL_SYS_WUQI_RESORT_OTHERATTR	= 100;	//rand otherattr

//返回成功还是失败
//const char CSL_CHECK_DIANZIKA	= 31;	//预留电子卡

const char CSL_STORAGE_PWD_OPEN			= 50;	//开启仓库密码
const char CSL_STORAGE_PWD_OPENOK		= 51;	//开启仓库密码ok
const char CSL_STORAGE_PWD_OPENERROR	= 52;	//开启仓库密码error
const char CSL_STORAGE_PWD_SET			= 53;	//设置仓库密码
const char CSL_STORAGE_PWD_SETOK		= 54;	//设置仓库密码ok
const char CSL_STORAGE_PWD_SETERROR		= 55;	//设置仓库密码error

const char CSL_LOOK_LIPIN		=56;  //察看礼品
const char CSL_LOOK_NOLIPIN		=57;  //没有礼品
const char CSL_LOOK_LIPININFO	=58;  //礼品信息
const char CSL_LOOK_GETLIPIN	=59;  //得到礼品



const char CSL_PANGUO					= 60;	//叛国

const char CSL_OTHER_TASK				= 61;	//完成任务



const char CSL_HITEGG_START			= 63;	//砸蛋开始
const char CSL_HITEGG_END			= 64;	//砸蛋结束
const char CSL_HITEGG_INFO			= 65;	//砸蛋返回信息//表示成功了
const char CSL_HITEGG_NOEMPTY		= 66;	//砸蛋返回没有空位置
const char CSL_HITEGG_HIT			= 67;	//砸蛋
const char CSL_HITEGG_HIT_SHIBAI	= 68;	//砸蛋失败

//------特定任务子集----//
const char CSL_TASK_QQ				= 1;	//qq任务
const int CSL_TASK_MAX				= 2;	//
//


//砸蛋 文敏辉
const char CSL_EGGKICK_REQUIRE    =127 ;   //请求砸蛋
const char CSL_EGGKICK_WINORLOSE  =126 ;  //砸蛋 赢 或 输
const char CSL_EGGKICK_GETREWARD  =125 ; //砸蛋 拿奖品
//砸蛋 文敏辉

const char CSL_WALLOW0                  = 70;
const char CSL_WALLOW1			        = 71;	// sammy 防沉迷 （3Hour-5H）
const char CSL_WALLOW2			        = 72;	// sammy 防沉迷  （>5H）


const char CSL_GUESS_ANSWER             =76;     //获取猜拳系统的答案信息 文敏辉

//const char GUESS_ANSWER_STONE           =1;     //石头
//const char GUESS_ANSWER_STONE           =1;     //剪刀
//const char GUESS_ANSWER_STONE           =1;     //布


const char CSL_GUOZHAN			= 80;	// 国战
const char CSL_GUOZHAN_END		= 81;	// 国战结束

const char CSL_LIHUN			= 90;	//离婚

const char CSL_WAIGUA			= 100;	//用外挂，自己测试
const char CSL_WAIGUA1			= 101;	//用外挂，自己测试
const char CSL_WAIGUA2			= 102;	//用外挂，自己测试
const char CSL_WAIGUA3			= 103;	//用外挂，自己测试

const char CSL_CHAXUN_MOBI			= 111;	//查询使用
const char CSL_CHAXUN_ITEM			= 112;	//查询使用
const char CSL_CHECK_BKDB			= 113;	//检测备份db是否正常
const char CSL_CHECK_LOGININ		= 114;	//

const char CHANGESCENE_NO_ITEM_MAP  = 115;	//地图道具限制

const char CSL_EVEN_BIND_MAC		= -57;	//绑定MAC

const char BKDB_NOINI			= 1;	//没有ini配置文件
const char BKDB_NOWRITE			= 2;	//不可写
const char BKDB_BIGINFO			= 3;	//大小信息

const long WG_BEGINSEE_ROLEID		= 28;
const long WG_ENDSEE_ROLEID			= 41;
const long WG_SKILL_ROLEID			= 37;
const long WG_TELEPORT_ROLEID		= 26;

const char WG_BEGINSEE		= 111;
const char WG_ENDSEE		= 112;
const char WG_SKILL			= 113;
const char WG_TELEPORT		= 114;
const char WG_PK_OPEN		= 120;
const char WG_PK_CLOSE		= 121;
const char WG_PUBLICSELL_OPEN = 122;
const char WG_PUBLICSELL_CLOSE = 123;
//g_pkOpened

// 骑士 骑士卫队长 男爵 子爵 伯爵 候爵 公爵 大公爵 总督 元帅 最高统帅
const char RANK_NULL		= 0;
const char RANK_QISHI		= 1;
const char RANK_QISHI_EX	= 2;
const char RANK_NANJUE		= 3;
const char RANK_ZHIJUE		= 4;
const char RANK_BOJUE		= 5;
const char RANK_HOUJUE		= 6;
const char RANK_GONGJUE		= 7;
const char RANK_DAGONGJUE	= 8;
const char RANK_ZONGDU		= 9;
const char RANK_YUANSHUAI		= 10;
const char RANK_ZUIGAOTONGSHUAI	= 11;
const char RANK_NUM				= 12;


const int PK_COLOR_YELLOW = 900;
const int PK_COLOR_RED = 2900;

//验证
const short l2l_login				= 1001;
const short l2l_check				= 1002;

const long CONST_MAX_PSELLTIME = 3 * 3600;	//拍卖过期时间
const long CONST_MAX_PSELLTIME_DOUBLE = 6 * 3600;

const short JIANYU_ID = 1501;

const long CONST_BACKHOME_COLDDOWN = 100000;	


const char PUBLICSELL_TIMETYPE_NORMAL = 0;
const char PUBLICSELL_TIMETYPE_DOUBLE = 1;
const char PUBLICSELL_TIMETYPE_DOUBLEDOUBLE = 2;	


const char PETFOOD_ERROE = 1 ;//参数错误
const char PETFOOD_BAO	= 2 ;//饥饿度不到喂养
const char PETFOOD_ITEMTYPE	= 3 ;//喂养材料不匹配
const char PETFOOD_ITEMNUM	= 4 ;//喂养材料数量不足

const char PETFOOD_RIDEERROR	= 5 ;//没有坐骑或不能喂养的坐骑

const char PETFOOD_OK	= 10 ;//喂养成功
const char PETFOOD_ADDEXP	= 101 ;//喂养一次只加经验
const char PETFOOD_UP	= 102 ;//喂养一次升级了
const char PETFOOD_UPOK	= 103 ;//喂养一次变成成体了
const char PETBODY_UPOK	= 104 ;//成体升级了
const char PETFOOD_EXPUP	= 105 ;//喂养次数增加

const char JILEI_EXP	= 110 ;//积累经验

enum EPingTaiType
{
	EPingTai_MWO			= 0,	    // 金酷自己
	EPingTai_TOM			= 1,		
	EPingTai_REAL			= 2,
	EPingTai_QQ				= 3,		//QQ
	EPingTai_HAOFANG		= 4,		//HAOFANG
	EPingTai_YOUYI			= 5,		//YOUYI
	EPingTai_17173			= 6,		//17173
	EPingTai_XUNLEI			= 7,		//迅雷
	EPingTai_EUHD			= 8,		//亿游
	EPingTai_MJ_WEISI		= 9,		//维思
	EPingTai_MJ_SHENGDA		= 10,		//盛大 add by coke 20090219
	EPingTai_MAX			= 11		//MAX
};

const short SCRIPT_CSL_ADDNPC		= 1;	//
const short SCRIPT_CSL_CHANGESCENE			= 2;	//
const short SCRIPT_CSL_DELETENPC			= 3;	//
const short SCRIPT_CSL_SETNPCSTATE			= 4;
//gbh修改文件mapserver
//scene_receive
//game_world

const int WENDA_TIME=30*1000;



const int LOGIN_LOG_IN			= 1;//
const int LOGIN_LOG_OUT			= 2;//
const int LOGIN_LOG_DELETE		= 3;//
const int LOGIN_LOG_CREATE		= 4;//

const short a2db_login				= 5001;
const short db2a_webeven			= 5088;
//技能伤害极限
const int g_iDamage1 =-1000000;
const int g_iDamage2 =1000000;
#endif
