//
//  ADBIndexedTableView.h
//  PassDesk
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//
//  ADBIndexedTableView inherits from UITableView (use it as a UITableView).
//
//  1. Set up delegate and dataSource as usual (using Interface Builder or programmatically).
//  2. Set indexDataSource and implement 'objectsFieldForIndexedTableView:' method
//     (used for sorting and indexing).
//  3. dataSource 'tableView:cellForRowAtIndexPath' implementation can retrieve object for
//     the given indexPath using 'objectAtIndexPath:' method.
//  4. Implementing 'indexedTableView:cellForRowAtIndexPath:usingObject:' is required
//     and it will be used only if 'tableView:cellForRowAtIndexPath' implementation is not
//     provided by the dataSource.
//  5. Reload the table sending unsorted objects via 'reloadDataWithObjects:' method to let
//     indexedTableView create the data structure. Use 'reloadData' for subsequent reloadings.
//

#import <UIKit/UIKit.h>
#import "ADBMessageInterceptor.h"

@class ADBIndexedTableView;

@protocol ADBIndexedTableViewDataSource <NSObject>

@required
/**
 @return field used to retrieve the first letter (used for index)
 @param tableView, the caller
 
 Return value will be used for KVC on 'indexedObjects' objects
 */
- (NSString *)objectsFieldForIndexedTableView:(ADBIndexedTableView *)tableView;

@optional
/**
 @return cell for row at index path
 @param tableView, the caller
 @param indexPath, the indexPath
 @param object, the object at indexPath
 
 Surrogate method for dataSource method 'tableView:cellForRowAtIndexPath:'
 Required only if 'tableView:cellForRowAtIndexPath' implementation is not provided by dataSource.
 */
- (UITableViewCell *)indexedTableView:(ADBIndexedTableView *)tableView
                cellForRowAtIndexPath:(NSIndexPath *)indexPath
                          usingObject:(id)object;
@end

@interface ADBIndexedTableView : UITableView {
    
    @private
    NSMutableDictionary *_indexedObjects;
    NSArray *_objectsInitials;
    ADBMessageInterceptor *_dataSourceInterceptor;
    id <ADBIndexedTableViewDataSource> __weak _indexDataSource;
}

/**
 @param objects, array of objects that will be organized in sections
 Surrogate method for 'reloadData', creates data structure and calls 'reloadData' on super
 Subsequent 'reloadData' messages use previously created data structure.
 */
- (void)reloadDataWithObjects:(NSArray *)objects;

- (id)objectAtIndexPath:(NSIndexPath *)indexPath;
- (void)removeObjectAtIndexPath:(NSIndexPath *)indexPath;
- (id)objectsWithInitials:(NSString *)initial;
- (id)objectsInSection:(NSUInteger)section;

@property (nonatomic, strong) NSMutableDictionary *indexedObjects;
@property (nonatomic, strong) NSArray *objectsInitials;
@property (nonatomic, weak) IBOutlet id <ADBIndexedTableViewDataSource> indexDataSource;

@end
