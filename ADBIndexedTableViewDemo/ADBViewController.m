//
//  ADBViewController.m
//  ADBIndexedTableViewDemo
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//

#import "ADBViewController.h"

@interface ADBViewController ()

@end

@implementation ADBViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    NSDictionary *obj1 = @{ @"name" : @"Annalisa" };
    NSDictionary *obj2 = @{ @"name" : @"Fabio" };
    NSDictionary *obj3 = @{ @"name" : @"Zeff" };
    NSDictionary *obj4 = @{ @"name" : @"Andrei" };
    NSDictionary *obj5 = @{ @"name" : @"Alberto" };
    NSDictionary *obj6 = @{ @"name" : @"Debo" };
    NSDictionary *obj7 = @{ @"name" : @"Luca" };
    NSDictionary *obj8 = @{ @"name" : @"Monica" };
    NSDictionary *obj9 = @{ @"name" : @"Laura" };
    NSDictionary *obj10 = @{ @"name" : @"Giuseppe" };
    NSDictionary *obj11 = @{ @"name" : @"Lucia" };
    NSDictionary *obj12 = @{ @"name" : @"Sarah" };
    NSDictionary *obj13 = @{ @"name" : @"Vera" };
    
    // unsorted objects
    NSArray *objects = @[obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10, obj11, obj12, obj13];
    
    [self.tableView reloadDataWithObjects:objects];
}

#pragma mark - ADBIndexedTableViewDataSource

- (NSString *)objectsFieldForIndexedTableView:(ADBIndexedTableView *)tableView
{
    return @"name";
}

- (UITableViewCell *)indexedTableView:(ADBIndexedTableView *)tableView
                cellForRowAtIndexPath:(NSIndexPath *)indexPath
                          usingObject:(id)object
{
    static NSString *identifier = @"Cell";
    UITableViewCell *cell = [self.tableView dequeueReusableCellWithIdentifier:identifier];
    
    if (cell == nil)
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
    
    NSDictionary *obj = object;
    cell.textLabel.text = [NSString stringWithFormat:@"%@ (via indexDataSource)", [obj valueForKey:@"name"]];
    
    return cell;
}

// otherwise we can implement original tableView:cellForRowAtIndexPath: method

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"Cell";
    UITableViewCell *cell = [self.tableView dequeueReusableCellWithIdentifier:identifier];

    if (cell == nil)
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];

    NSDictionary *obj = [self.tableView objectAtIndexPath:indexPath];
    cell.textLabel.text = [NSString stringWithFormat:@"%@ (via dataSource)", [obj valueForKey:@"name"]];

    return cell;
}

@end
