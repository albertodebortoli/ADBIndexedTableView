//
//  ADBMessageInterceptor.h
//  PassDesk
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//
//  MessageInterceptor, proxy class to handle message forwarding.
//
//  If you set a message inspector as a delegate object (for your delegating object)
//  it will check if the real delegate (receiver) can respond to the message, otherwise
//  it will check if the surrogate delegate (secondChance) can handle the message.
//  If both tests fail, a check on super (NSObject) will be performed as last wish.
//
//  Useful to let a class (instance I) implement some delegate methods and to let the
//  rest of the delegate methods be implemented by the real delegate (R).
//  In this scenario receiver must be the real delegate (R) and mainInTheMiddle must be the class object (I).
//
//  Classes that encapsulate a interceptor must:
//  1. hold a ADBMessageInterceptor *iVar (here named _delegateInterceptor)
//  2. implement the following methods
//
//  example given using UITableViewDelegate
//
//  #pragma mark - Message forwarding
//
//  - (id <UITableViewDelegate>)delegate
//  {
//      return (id <UITableViewDelegate>)_delegateInterceptor;
//  }
//
//  - (void)setDelegate:(id <UITableViewDelegate>)delegate
//  {
//      [super setDelegate:nil];
//
//      _delegateInterceptor = [[ADBMessageInterceptor alloc] init];
//      [_delegateInterceptor setSecondChance:self];
//      [_delegateInterceptor setReceiver:delegate];
//
//      [super setDelegate:(id)_delegateInterceptor];
//  }
//

#import <Foundation/Foundation.h>

@interface ADBMessageInterceptor : NSObject {
    
    id __weak _receiver;
    id __weak _secondChance;
}

@property (nonatomic, weak) id receiver;
@property (nonatomic, weak) id secondChance;

@end
