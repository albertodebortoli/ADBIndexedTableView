//
//  ADBViewController.h
//  ADBIndexedTableViewDemo
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ADBIndexedTableView.h"

@interface ADBViewController : UIViewController
<UITableViewDelegate,
UITableViewDataSource,
ADBIndexedTableViewDataSource>

@property (nonatomic, strong) IBOutlet ADBIndexedTableView *tableView;

@end
