ADBIndexedTableView
===========================

Indexed UITableView using first letter objects property.
ADBIndexedTableView uses introspection and message forwarding.

Try out the included demo project.

If you'd like to include this component as a pod using [CocoaPods](http://cocoapods.org/), just add the following line to your Podfile: `pod "ADBIndexedTableView"`

Simple usage:
- copy ADBIndexedTableView and ADBMessageInterceptor classes into your project
- import `ADBIndexedTableView.h` in your class
- create an ADBIndexedTableView as usually done with UITableView
- set up delegate and dataSource as usual (using Interface Builder or programmatically)
- set `indexDataSource` and implement `objectsFieldForIndexedTableView:` method (used for sorting and indexing)

``` objective-c
#pragma mark - ADBIndexedTableViewDataSource
- (NSString *)objectsFieldForIndexedTableView:(ADBIndexedTableView *)tableView {
	return objectPropertyAsString;
}
```

- dataSource `tableView:cellForRowAtIndexPath:` implementation can retrieve object for the given indexPath using `objectAtIndexPath:` method
- implementation of `indexedTableView:cellForRowAtIndexPath:usingObject:` is required and it will be used only if `tableView:cellForRowAtIndexPath:` implementation is not provided by the dataSource.

``` objective-c
- (UITableViewCell *)indexedTableView:(ADBIndexedTableView *)tableView
                cellForRowAtIndexPath:(NSIndexPath *)indexPath
                    	  usingObject:(id)object { ... }
```

- reload the table sending unsorted objects via `reloadDataWithObjects:` method to let indexedTableView create the data structure. Use `reloadData` for subsequent reloads.

``` objective-c
{
	... // retrieve objects
	NSArray *objects = @[...] // objects retrieved
    [self.tableView reloadDataWithObjects:objects];
}
```

![1](https://s3.amazonaws.com/albertodebortoli.github.com/images/adbindexedtableview/indexed_01.png)
![2](https://s3.amazonaws.com/albertodebortoli.github.com/images/adbindexedtableview/indexed_02.png)

# License

Licensed under the New BSD License.

Copyright (c) 2013, Alberto De Bortoli
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Alberto De Bortoli nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Alberto De Bortoli BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## Resources

Info can be found on [my website](http://www.albertodebortoli.com), [and on Twitter](http://twitter.com/albertodebo).