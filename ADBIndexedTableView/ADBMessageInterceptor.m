//
//  ADBMessageInterceptor.m
//  ADBIndexedTableView
//  v1.1.0
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//

#import "ADBMessageInterceptor.h"

@implementation ADBMessageInterceptor

- (id)forwardingTargetForSelector:(SEL)aSelector
{
    if ([_receiver respondsToSelector:aSelector]) {
        return _receiver;
    }
    if ([_secondChance respondsToSelector:aSelector]) {
        return _secondChance;
    }
    return [super forwardingTargetForSelector:aSelector];
}

- (BOOL)respondsToSelector:(SEL)aSelector
{
    if ([_receiver respondsToSelector:aSelector]) {
        return YES;
    }
    if ([_secondChance respondsToSelector:aSelector]) {
        return YES;
    }
    return [super respondsToSelector:aSelector];
}

@end
