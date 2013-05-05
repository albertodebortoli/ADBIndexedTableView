//
//  ADBMessageInterceptor.h
//  ADBIndexedTableView
//  v1.1.0
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//

/** ADBMessageInterceptor is proxy class to handle message forwarding.

  Message inspector act as a proxy for the delegate object (for your delegant object). It will check if the real delegate (receiver) can respond to the message, otherwise it will check if the surrogate delegate (secondChance) can handle the message. If both tests fail, a check on super (NSObject) will be performed as last wish.

  Using message inspector is useful to let an instance I implement some delegate methods and let the rest of the delegate methods to be implemented by the real delegate R. In this scenario receiver must be the real delegate R and secondChance must be the object I.

  Classes that encapsulate a interceptor as a proxy for delegate objects must:
 
  1. hold ADBMessageInterceptor *iVars (one here named __delegateInterceptor_)
  2. implement the following accessor methods for the delegate object properties (one here named _delegate_)

  example given using UITableViewDelegate

    #pragma mark - Message forwarding

    - (id <UITableViewDelegate>)delegate
    {
        return (id <UITableViewDelegate>)_delegateInterceptor;
    }
 
    - (void)setDelegate:(id <UITableViewDelegate>)delegate
    {
        [super setDelegate:nil];

        _delegateInterceptor = [[ADBMessageInterceptor alloc] init];
        [_delegateInterceptor setSecondChance:self];
        [_delegateInterceptor setReceiver:delegate];

        [super setDelegate:(id)_delegateInterceptor];
    }
*/

#import <Foundation/Foundation.h>

@interface ADBMessageInterceptor : NSObject

#pragma mark - Properties

/**
 Reference to the delegate object providing the indexDataSource
 */
@property (nonatomic, weak) id receiver;

/**
 Reference to the second chance delegate object
 */
@property (nonatomic, weak) id secondChance;

@end
