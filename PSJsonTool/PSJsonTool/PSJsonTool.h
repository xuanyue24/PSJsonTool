//
//  PSJsonTool.h
//  PSJsonTool
//
//  Created by 罗烨 on 15/5/30.
//  Copyright © 2016年 luoye. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol PSJsonSerializationDelegate <NSObject>

@required

///作用:建立一个映射 将原Json中的字段对应于model中的某一个属性
///如果后台返回了字段为 user_name 而在model对应的属性为
///@property(nonatomic,copy) NSString *userName;
///那么只需要在返回的字典中添加 @"userName" : @"user_name"的键值对即可
+ (NSDictionary *)jsonKeyConvertToPropertyKey;

@optional

//作用:将基本数据类型转化为OC对象,转化函数返回值必须是NSObject子类，本身属性非NSObject子类的会自动转化，如
//本身属性      返回值类型     转化后
//BOOL         NSNumber     !=0 为YES ==0 为NO
//其他数字类型   NSNumber     与NSNumber同值
+ (NSDictionary *)jsonValueConverter;

//作用：对某些属性进行进一步的转化操作,操作内容为block,转化block返回值必须是NSString类型或其子类
+ (NSDictionary *)objcValueConverter;

//作用:有些属性不需要在对象转json时被用到,把不需要转化的属性的key进行指定
+ (NSArray *)IgnoreKeyWhenConvertToJson;

//作用:很多时候可能会出现模型的嵌套,一个json对象返回的数据中可能会有dictionary array的嵌套情况,而且嵌套的部分可能对应
//于一种模型,这时候可以指定在jsonToModel时嵌套的model的类型
+ (NSDictionary *)keyClass;


@end

@interface PSJsonTool : NSObject

/**
 * obj 转 json 暂时以递归方式实现
 * @param obj 需要转换为json的对象
 * @param jsonAddr  输出json字串地址
 * @param key 输出json字串是否需要加额外的键，不加传nil
 * @param baseClass 被转换的对象的类型
 * @param preKey 当前被转换的对象对应的key值
 */
+(void)objToJson: (id)obj  out: (NSMutableString **)jsonAddr withKey: (NSString *)key baseClass: (Class)baseClass preKey: (NSString *)preKey;

//快捷转换方法---实质上调用了上面的方法
+(NSString *)objToJson: (id)obj withKey: (NSString *)key;

//json转换指定的oc对象方法,mcclass代表需要转化成的对象的类别
+(id)jsonToObj: (NSString *)json asClass: (Class)mclass;

//keyclass是当json中存在一个dictionary或者array时,可以通过keyclass字典指定这个字典中所对应的各个成员的内容是什么
+(id)jsonToObj:(NSString *)json asClass:(Class)mclass WithKeyClass: (NSDictionary *) keyClass;

//一般地,json在经过序列化后(比如说AFN返回时会序列化)会成为一个NSDictionary或者NSArray对象,这时候转换成指定的oc对象时调用的
//方法
+(id)rootObjToObj: (id)jsonObj asClass:(Class)mclass WithKeyClass: (NSDictionary *) keyClass;

//上面方法的快捷方法,推荐被转换的oc对象将keyclass对应的字典写在协议方法的返回值中
+(id)rootObjToObj: (id)jsonObj asClass:(Class)mclass;



@end
