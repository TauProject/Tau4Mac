//
//  TauMeTubePlayground.m
//  Tau4Mac
//
//  Created by Tong G. on 3/28/16.
//  Copyright © 2016 Tong Kuo. All rights reserved.
//

#import "TauMeTubePlayground.h"
#import "TauToolbarItem.h"

// TauMeTubePlayground class
@implementation TauMeTubePlayground
    {
    // Layouts cache
    NSArray <NSLayoutConstraint*> __strong* selectedPinEdgesCache_;
    }

#pragma mark - Relay the Delicious of TauToolbarController

// Relay the delicious that will be used to feed the singleton of TauToolbarController class

// Relay the title bar accessory view controller
// from current selected instances of TauMeTubeTabItem to the TauMeTubeContentSubViewController
@dynamic titlebarAccessoryViewControllerWhileActive;
+ ( NSSet <NSString*>* ) keyPathsForValuesAffectingTitlebarAccessoryViewControllerWhileActive
    {
    return [ NSSet setWithObjects: TauKVOStrictKey( selectedTabs ), nil ];
    }

- ( NSTitlebarAccessoryViewController* ) titlebarAccessoryViewControllerWhileActive
    {
    return [ self.selectedTabs.firstObject.viewController valueForKey: TauKVOStrictKey( titlebarAccessoryViewControllerWhileActive ) ];
    }

// Relay the Tau toolbar items
// from current selected instances of TauMeTubeTabItem to the TauMeTubeContentSubViewController
@dynamic exposedToolbarItemsWhileActive;
+ ( NSSet <NSString*>* ) keyPathsForValuesAffectingExposedToolbarItemsWhileActive
    {
    return [ NSSet setWithObjects: TauKVOStrictKey( selectedTabs ), nil ];
    }

- ( NSArray <TauToolbarItem*>* ) exposedToolbarItemsWhileActive
    {
    return [ self.selectedTabs.firstObject.viewController valueForKey: TauKVOStrictKey( exposedToolbarItemsWhileActive ) ];
    }

#pragma mark - External KVB Comliant Properties

@synthesize selectedTabs = selectedTabs_;
+ ( BOOL ) automaticallyNotifiesObserversOfSelectedTabs
    {
    return NO;
    }

- ( void ) setSelectedTabs: ( NSArray <TauMeTubeTabItem*>* )_New
    {
    if ( selectedTabs_ != _New )
        {
        [ self willChangeValueForKey: TauKVOStrictKey( selectedTabs ) ];

        TauMeTubeTabItem* oldSelected = self.selectedTabs.firstObject;
        if ( oldSelected && oldSelected.viewController )
            {
            [ oldSelected.viewController removeFromParentViewController ];
            [ oldSelected.viewController.view removeFromSuperview ];

            if ( selectedPinEdgesCache_ )
                {
                [ self removeConstraints: selectedPinEdgesCache_ ];
                selectedPinEdgesCache_ = nil;
                }
            }

        selectedTabs_ = _New;

        TauMeTubeTabItem* newSelected = self.selectedTabs.firstObject;
        [ self addSubview: newSelected.viewController.view ];
        selectedPinEdgesCache_ = [ newSelected.viewController.view autoPinEdgesToSuperviewEdges ];

        [ newSelected.viewController setValue: newSelected.repPlaylistIdentifier forKey: TauKVOStrictKey( playlistIdentifier ) ];

        [ self didChangeValueForKey: TauKVOStrictKey( selectedTabs ) ];
        }
    }

- ( NSArray <TauMeTubeTabItem*>* ) selectedTabs
    {
    return selectedTabs_;
    }

- ( NSUInteger ) countOfSelectedTabs
    {
    return selectedTabs_.count;
    }

- ( NSArray <TauMeTubeTabItem*>* ) selectedTabsAtIndexes: ( NSIndexSet* )_Indexes
    {
    return [ selectedTabs_ objectsAtIndexes: _Indexes ];
    }

- ( void ) getSelectedTabs: ( out TauMeTubeTabItem* __unsafe_unretained* )_Buffer range: ( NSRange )_InRange
    {
    [ selectedTabs_ getObjects: _Buffer range: _InRange ];
    }

@end // TauMeTubePlayground class



// ------------------------------------------------------------------------------------------------------------ //



// TauMeTubeTabItem class
@implementation TauMeTubeTabItem

@synthesize tabTitle = tabTitle_;
@synthesize repPlaylistName = repPlaylistName_;
@synthesize repPlaylistIdentifier = repPlaylistIdentifier_;
@synthesize viewController = viewController_;

#pragma mark - Initializations

- ( instancetype ) initWithTitle: ( NSString* )_Title playlistName: ( NSString* )_PlaylistName playlistIdentifier: ( NSString* )_PlaylistId viewController: ( NSViewController* )_ViewController
    {
    if ( self = [ super init ] )
        {
        self.tabTitle = _Title;
        self.repPlaylistName = _PlaylistName;
        self.repPlaylistIdentifier = _PlaylistId;
        self.viewController = _ViewController;

        [ _ViewController setValue: self.repPlaylistName forKey: TauKVOStrictKey( playlistName ) ];
        }

    return self;
    }

@end // TauMeTubeTabItem class