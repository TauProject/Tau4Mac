//
//  TauSearchResultsCollectionContentSubViewController.m
//  Tau4Mac
//
//  Created by Tong G. on 3/20/16.
//  Copyright © 2016 Tong Kuo. All rights reserved.
//

#import "TauSearchResultsCollectionContentSubViewController.h"
#import "TauToolbarItem.h"
#import "TauContentCollectionViewController.h"

// TauSearchResultsAccessoryBarViewController class
@interface TauSearchResultsAccessoryBarViewController : NSTitlebarAccessoryViewController
@end // TauSearchResultsAccessoryBarViewController class



// ------------------------------------------------------------------------------------------------------------ //



// Private
@interface TauSearchResultsCollectionContentSubViewController ()

// Model: Feed me, if you dare.
@property ( strong, readwrite ) NSArray <GTLYouTubeSearchResult*>* searchResults;   // KVB-compliant
@property ( strong, readwrite ) NSString* prevToken_;   // KVB-compliant
@property ( strong, readwrite ) NSString* nextToken_;   // KVB-compliant
@property ( assign, readwrite, setter = setPaging: ) BOOL isPaging;   // KVB compliant

@property ( weak ) IBOutlet TauSearchResultsAccessoryBarViewController* accessoryBarViewController_;
@property ( strong, readonly ) TauContentCollectionViewController* collectionViewController_;
@property ( strong, readonly ) TauYTDataServiceCredential* credential_;

- ( void ) executeSearchWithPageToken_: ( NSString* )_PageToken;

@end // Private



// ------------------------------------------------------------------------------------------------------------ //



// TauSearchResultsCollectionContentSubViewController class
@implementation TauSearchResultsCollectionContentSubViewController
    {
    TauYTDataServiceCredential __strong* priCredential_;
    NSDictionary __strong* priOriginalOperationsCombination_;
    TauContentCollectionViewController __strong* priCollectionViewController_;
    }

#pragma mark - Initializations

- ( instancetype ) initWithNibName: ( NSString* )_NibNameOrNil bundle: ( NSBundle* )_NibBundleOrNil
    {
    if ( self = [ super initWithNibName: _NibNameOrNil bundle: _NibBundleOrNil ] )
        ;
    return self;
    }

#pragma mark - Actions

- ( IBAction ) loadPrevPageAction: ( id )_Sender
    {
    [ self executeSearchWithPageToken_: self.prevToken_ ];
    }

- ( IBAction ) loadNextPageAction: ( id )_Sender
    {
    [ self executeSearchWithPageToken_: self.nextToken_ ];
    }

- ( IBAction ) cancelAction: ( id )_Sender
    {
    [ [ TauYTDataService sharedService ] unregisterConsumer: self withCredential: priCredential_ ];
    [ self popMe ];
    }

#pragma mark - Overrides

- ( NSTitlebarAccessoryViewController* ) titlebarAccessoryViewControllerWhileActive
    {
    return self.accessoryBarViewController_;
    }

#pragma mark - External KVB Compliant

@synthesize searchText = searchText_;
+ ( BOOL ) automaticallyNotifiesObserversOfSearchText
    {
    return NO;
    }

- ( void ) setSearchText: ( NSString* )_New
    {
    if ( searchText_ != _New )
        {
        [ self willChangeValueForKey: @"searchText" ];
        searchText_ = _New;

        priOriginalOperationsCombination_ =
            @{ TauTDSOperationMaxResultsPerPage : @50, TauTDSOperationRequirements : @{ TauTDSOperationRequirementQ : searchText_ }, TauTDSOperationPartFilter : @"snippet" };

        [ self executeSearchWithPageToken_: nil ];
        [ self didChangeValueForKey: @"searchText" ];
        }
    }

- ( NSString* ) searchText
    {
    return searchText_;
    }

@dynamic hasPrev;
+ ( NSSet <NSString*>* ) keyPathsForValuesAffectingHasPrev
    {
    return [ NSSet setWithObjects: @"prevToken_", nil ];
    }

- ( BOOL ) hasPrev
    {
    return ( self.prevToken_ != nil );
    }

@dynamic hasNext;
+ ( NSSet <NSString*>* ) keyPathsForValuesAffectingHasNext
    {
    return [ NSSet setWithObjects: @"nextToken_", nil ];
    }

- ( BOOL ) hasNext
    {
    return ( self.nextToken_ != nil );
    }

@synthesize isPaging = isPaging_;
+ ( BOOL ) automaticallyNotifiesObserversOfIsPaging
    {
    return NO;
    }

- ( void ) setPaging: ( BOOL )_Flag
    {
    if ( isPaging_ != _Flag )
        {
        [ self willChangeValueForKey: @"isPaging" ];
        isPaging_ = _Flag;
        [ self didChangeValueForKey: @"isPaging" ];
        }
    }

- ( BOOL ) isPaging
    {
    return isPaging_;
    }

#pragma mark - Internal KVB Compliant

@synthesize searchResults = searchResults_;
- ( NSUInteger ) countOfSearchResults
    {
    return searchResults_.count;
    }

- ( NSArray <GTLYouTubeSearchResult*>* ) searchResultsAtIndexes: ( NSIndexSet* )_Indexes
    {
    return [ searchResults_ objectsAtIndexes: _Indexes ];
    }

- ( void ) getSearchResults: ( GTLYouTubeSearchResult* __unsafe_unretained* )_Buffer range: ( NSRange )_InRange
    {
    [ searchResults_ getObjects: _Buffer range: _InRange ];
    }

@synthesize prevToken_;
@synthesize nextToken_;

#pragma mark - Private

@synthesize accessoryBarViewController_;

@dynamic collectionViewController_;
- ( TauContentCollectionViewController* ) collectionViewController_
    {
    if ( !priCollectionViewController_ )
        {
        priCollectionViewController_ = [ [ TauContentCollectionViewController alloc ] initWithNibName: nil bundle: nil ];
        [ self addChildViewController: priCollectionViewController_ ];
        [ self.view addSubview: priCollectionViewController_.view ];
        [ priCollectionViewController_.view autoPinEdgesToSuperviewEdges ];
        }

    return priCollectionViewController_;
    }

@dynamic credential_;
- ( TauYTDataServiceCredential* ) credential_
    {
    if ( !priCredential_ )
        {
        priCredential_ =
            [ [ TauYTDataService sharedService ] registerConsumer: self
                                              withMethodSignature: [ self methodSignatureForSelector: _cmd ]
                                                  consumptionType: TauYTDataServiceConsumptionSearchResultsType ];
        }

    return priCredential_;
    }

- ( void ) executeSearchWithPageToken_: ( NSString* )_PageToken
    {
    NSDictionary* operationsCombination = nil;
    if ( _PageToken && ( _PageToken.length > 0 ) )
        {
        NSMutableDictionary* modified = [ NSMutableDictionary dictionaryWithDictionary: priOriginalOperationsCombination_ ];
        [ modified setObject: _PageToken forKey: TauTDSOperationPageToken ];
        operationsCombination = modified;
        }
    else
        operationsCombination = priOriginalOperationsCombination_;

    self.isPaging = ( _PageToken != nil );
    [ [ TauYTDataService sharedService ] executeConsumerOperations: operationsCombination
                                                    withCredential: self.credential_
                                                           success:
    ^( NSString* _PrevPageToken, NSString* _NextPageToken )
        {
        DDLogDebug( @"%@", self.searchResults );

        self.prevToken_ = _PrevPageToken;
        self.nextToken_ = _NextPageToken;
        self.isPaging = NO;

        [ self.collectionViewController_ reloadData ];
        } failure: ^( NSError* _Error )
            {
            DDLogRecoverable( @"Failed to execute the searching due to {%@}.", _Error );
            self.isPaging = NO;
            } ];
    }

@end // TauSearchResultsCollectionContentSubViewController class



// ------------------------------------------------------------------------------------------------------------ //



// TauSearchResultsAccessoryBarViewController class
@implementation TauSearchResultsAccessoryBarViewController
@end // TauSearchResultsAccessoryBarViewController class