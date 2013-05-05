//
//  ADBIndexedTableView.m
//  ADBIndexedTableView
//  v1.1.0
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//

#import "ADBIndexedTableView.h"

@interface ADBIndexedTableView ()

@property (nonatomic, strong) ADBMessageInterceptor *dataSourceInterceptor;

@end

@implementation ADBIndexedTableView

#pragma mark - Message forwarding

- (id <UITableViewDataSource>)dataSource
{
    return (id <UITableViewDataSource>)_dataSourceInterceptor;
}

- (void)setDataSource:(id <UITableViewDataSource>)dataSource
{
    [super setDataSource:nil];
    
    _dataSourceInterceptor = [[ADBMessageInterceptor alloc] init];
    [_dataSourceInterceptor setReceiver:dataSource];
    [_dataSourceInterceptor setSecondChance:self];

    [super setDataSource:(id)_dataSourceInterceptor];
}

#pragma mark - Core

- (void)reloadDataWithObjects:(NSArray *)objects
{
    NSString *field = [self.indexDataSource objectsFieldForIndexedTableView:self];
    
    NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:field ascending:YES];
    objects = [objects sortedArrayUsingDescriptors:@[sortDescriptor]];
    
    // calculate needed initials
    NSMutableArray *initials = [NSMutableArray array];
    for (NSString *property in [objects valueForKey:field]) {
        if ([property length]) {
            NSString *initial = [[property substringToIndex:1] capitalizedString];
            if (![initials containsObject:initial]) {
                [initials addObject:initial];
            }
        }
    }
    
    self.objectsInitials = initials;
    
    self.indexedObjects = [NSMutableDictionary dictionary];
    
    // create dictionary with objects grouped by initial
    for (NSString *initial in self.objectsInitials) {
        NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF.%@ beginswith[cd] %@", field, initial];
        NSArray *filteredForInitial = [objects filteredArrayUsingPredicate:predicate];
        [self.indexedObjects setObject:filteredForInitial forKey:initial];
    }
    
    [self reloadData];
}

- (id)objectAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *initial = self.objectsInitials[indexPath.section];
    return self.indexedObjects[initial][indexPath.row];
}

- (void)removeObjectAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *initial = self.objectsInitials[indexPath.section];
    NSMutableArray *objectsForGivenInitial = [self.indexedObjects[initial] mutableCopy];
    [objectsForGivenInitial removeObjectAtIndex:indexPath.row];
    [self.indexedObjects setObject:objectsForGivenInitial forKey:initial];
    [self deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationRight];
}

- (id)objectsWithInitials:(NSString *)initial
{
    NSArray *retVal = self.indexedObjects[[initial uppercaseString]];
    return retVal;
}

- (id)objectsInSection:(NSUInteger)section
{
    NSString *initial = [self.objectsInitials objectAtIndex:section];
    NSArray *retVal = self.indexedObjects[initial];
    return retVal;
}

#pragma mark - UITableViewDatasource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return [self.objectsInitials count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    NSString *initial = self.objectsInitials[section];
    return [self.indexedObjects[initial] count];
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return self.objectsInitials[section];
}

- (NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView
{
    return self.objectsInitials;
}

- (NSInteger)tableView:(UITableView *)tableView
sectionForSectionIndexTitle:(NSString *)title
               atIndex:(NSInteger)index
{
    return [self.objectsInitials indexOfObject:title];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    id objectAtIndexPath = [self objectAtIndexPath:indexPath];
    
    UITableViewCell *cell = nil;
    
    // since indexedTableView:cellForRowAtIndexPath:usingObject: is marked as @optional
    // we should check if indexDataSource responds to it, but if we get here, dataSource does not implement
    // tableView:cellForRowAtIndexPath:, therefore indexDataSource must implement
    // indexedTableView:cellForRowAtIndexPath:usingObject: (required in this scenario)
    cell = [self.indexDataSource indexedTableView:self
                            cellForRowAtIndexPath:indexPath
                                      usingObject:objectAtIndexPath];
    
    return cell;
}

@end
