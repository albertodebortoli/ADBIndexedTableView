//
//  ADBIndexedTableView.h
//  ADBIndexedTableView
//  v1.1.0
//
//  Created by Alberto De Bortoli on 11/4/12.
//  Copyright (c) 2012 Alberto De Bortoli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ADBMessageInterceptor.h"

@class ADBIndexedTableView;

/** The dataSource of a ADBIndexedTableView object must adopt the ADBIndexedTableViewDataSource protocol.
 
 - Required method objectsFieldForIndexedTableView: of the protocol allow the delegate to provide a KVC value for sorting data.
 - Optional method indexedTableView:cellForRowAtIndexPath:usingObject: of the protocol allow the delegate to manage cells instead of using tableView:cellForRowAtIndexPath: UITableViewDataSource protocol method.
 */

@protocol ADBIndexedTableViewDataSource <NSObject>

@required
/**
 Return value will be used for KVC on indexedObjects objects
 
 @return field used to retrieve the first letter (used for index)
 @param tableView the caller
 */
- (NSString *)objectsFieldForIndexedTableView:(ADBIndexedTableView *)tableView;

@optional
/**
 Surrogate method for dataSource method tableView:cellForRowAtIndexPath:
 Required only if tableView:cellForRowAtIndexPath: implementation is not provided by dataSource.
 
 @return cell for row at index path
 @param tableView the caller
 @param indexPath the indexPath
 @param object the object at indexPath
 */
- (UITableViewCell *)indexedTableView:(ADBIndexedTableView *)tableView
                cellForRowAtIndexPath:(NSIndexPath *)indexPath
                          usingObject:(id)object;
@end

/**  ADBIndexedTableView inherits from UITableView (use it as a UITableView).
 
 1. Set up delegate and dataSource as usual (using Interface Builder or programmatically);
 2. Set indexDataSource and implement objectsFieldForIndexedTableView: method
 (used for sorting and indexing);
 3. DataSource tableView:cellForRowAtIndexPath: implementation can retrieve object for
 the given indexPath using objectAtIndexPath: method;
 4. Implementation of indexedTableView:cellForRowAtIndexPath:usingObject: is required
 and it will be used only if tableView:cellForRowAtIndexPath: implementation is not
 provided by the dataSource;
 5. Reload the table sending unsorted objects via reloadDataWithObjects: method to let
 indexedTableView create the data structure. Use reloadData for subsequent reloads.
 */

@interface ADBIndexedTableView : UITableView

#pragma mark - Instance methods

/**
 Surrogate method for reloadData, creates data structure and calls reloadData on super
 Subsequent reloadData messages use previously created data structure.
 
 @param objects array of objects that will be organized in sections
 */
- (void)reloadDataWithObjects:(NSArray *)objects;

/**
 Retrieves from the datasource the object at a given indexpath
 
 @return the object at a given indexPath
 @param indexPath the indexpath
 */
- (id)objectAtIndexPath:(NSIndexPath *)indexPath;

/**
 Removes the object at a given indexpath
 
 @param indexPath the indexpath
 */
- (void)removeObjectAtIndexPath:(NSIndexPath *)indexPath;

/**
 Retrieves from the datasource the objects with a given initial
 
 @return the objects with a given initial
 @param initial the initial (i.e. the section)
 */
- (id)objectsWithInitials:(NSString *)initial;

/**
 Retrieves from the datasource the objects at a given section
 
 @return the objects at a given section
 @param section the section
 */
- (id)objectsInSection:(NSUInteger)section;

#pragma mark - Properties

/**
 Dictionary of objects grouped by initial
 */
@property (nonatomic, strong) NSMutableDictionary *indexedObjects;

/**
 Array of initials
 */
@property (nonatomic, strong) NSArray *objectsInitials;

/**
 Reference to the delegate object providing the indexDataSource
 */
@property (nonatomic, weak) IBOutlet id <ADBIndexedTableViewDataSource> indexDataSource;

@end
