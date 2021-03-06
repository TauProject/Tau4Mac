//
//  TauConstants.h
//  Tau4Mac
//
//  Created by Tong G. on 3/8/16.
//  Copyright © 2016 Tong Kuo. All rights reserved.
//

#ifndef TauConstants_h
#define TauConstants_h



// ------------------------------------------------------------------------------------------------------------ //



#define TauPreferredQueue( DISPATCH_QUEUE ) DISPATCH_QUEUE ?: dispatch_get_main_queue()
#define TauExecuteCodeFragmentOnMainQueue( FRAGMENT ) \
dispatch_async( dispatch_get_main_queue(), ( dispatch_block_t )^{ do { FRAGMENT; } while ( 0 ); } )

#define TauKeyOfSel( _Sel ) ( NSStringFromSelector( _Sel ) )

#define TauKVOLiberalKey( _Sel ) \
TAU_SUPPRESS_UNDECLARED_SELECTOR_WARNING_BEGIN \
    TauKeyOfSel( @selector( _Sel ) ) \
TAU_SUPPRESS_UNDECLARED_SELECTOR_WARNING_COMMIT

#define TauKVOStrictKey( _Sel ) \
TAU_FATAL_UNDECLARED_SELECTOR_WARNING_BEGIN \
    TauKeyOfSel( @selector( _Sel ) ) \
TAU_FATAL_UNDECLARED_SELECTOR_WARNING_COMMIT

#define TauKVOStrictClassKeyPath( _CLASS, _KEYPATH ) \
FBKVOClassKeyPath( _CLASS, _KEYPATH )

#define TAU_CHANGE_VALUE_BEGIN( _Key )  ( [ self willChangeValueForKey: _Key ] )
#define TAU_CHANGE_VALUE_COMMIT( _Key ) ( [ self didChangeValueForKey: _Key ] )

#define TAU_CHANGE_VALUE_BEGIN_of( _Sel )  TAU_CHANGE_VALUE_BEGIN( TauKeyOfSel( _Sel ) )
#define TAU_CHANGE_VALUE_COMMIT_of( _Sel ) TAU_CHANGE_VALUE_COMMIT( TauKeyOfSel( _Sel ) )

#define TauChangeValueForKVOStrictKey( _Key, _ExpressionBlk ) \
do { \
TAU_FATAL_UNDECLARED_SELECTOR_WARNING_BEGIN \
    TAU_CHANGE_VALUE_BEGIN( TauKVOStrictKey( _Key ) ); \
        _ExpressionBlk(); \
    TAU_CHANGE_VALUE_COMMIT( TauKVOStrictKey( _Key ) ); \
TAU_FATAL_UNDECLARED_SELECTOR_WARNING_COMMIT \
} while ( 0 )

#define TauLiberalAssert( CONDITION, BOOLPTR, FRMT, ... ) \
do { \
BOOL passed = ( CONDITION ); \
if ( !passed ) { \
NSString* desc = [ NSString stringWithFormat: FRMT, ## __VA_ARGS__ ]; \
DDLogFatal( @"%@", desc ); \
} \
BOOL* boolptr = BOOLPTR; \
if ( boolptr ) *boolptr = passed; \
} while ( 0 )

#define TauStrictAssert( CONDITION, FRMT, ... ) \
do { \
BOOL passed = NO; \
TauLiberalAssert( CONDITION, &passed, FRMT, __VA_ARGS__ ); \
if ( !passed ) assert( CONDITION ); \
} while ( 0 )

#define TauAssertCondition( CONDITION ) \
TauStrictAssert( CONDITION, @"condition not satisfied: %s", #CONDITION )

#ifdef TAU_PRIVATE
#   undef TAU_PRIVATE
#endif

#define TAU_PRIVATE static



// ------------------------------------------------------------------------------------------------------------ //



#define TauDeallocBegin - ( void ) dealloc { DDLogExpecting( @"%@ got deallocated", self );
#define TauDeallocEnd }

#define TauMutuallyBind( _Lhs, _LhsKeyPath, _Rhs, _RhsKeyPath ) \
do { \
[ _Lhs bind: _LhsKeyPath toObject: _Rhs withKeyPath: _RhsKeyPath options: nil ]; \
[ _Rhs bind: _RhsKeyPath toObject: _Lhs withKeyPath: _LhsKeyPath options: nil ]; \
} while ( 0 )

#define TauMutuallyUnbind( _Lhs, _LhsKeyPath, _Rhs, _RhsKeyPath ) \
do { \
[ _Lhs unbind: _LhsKeyPath ]; \
[ _Rhs unbind: _RhsKeyPath ]; \
} while ( 0 )



// ------------------------------------------------------------------------------------------------------------ //



NSString extern* const TauKeychainItemName;

#pragma mark - Client Credentials

/** The OAuth 2.0 client ID for Tau4Mac. Examine this value here https://console.developers.google.com/ */
NSString extern* const TauClientID;

/** The client secret associated with client ID of Tau4Mac. */
NSString extern* const TauClientSecret;

#pragma mark - Auth Scopes

/** Manage users' YouTube account. This scope requires communication with the API server to happen over an SSL connection. */
NSString extern* const TauManageAuthScope;

/** View users' YouTube account. */
NSString extern* const TauReadonlyAuthScope;

/** Upload YouTube videos and manage users' YouTube videos. */
NSString extern* const TauUploadAuthScope;

/** Retrieve the auditDetails part in a channel resource. */
NSString extern* const TauPartnerChannelAuditAuthScope;



// ------------------------------------------------------------------------------------------------------------ //



#define TauUIUnknownPlaceholder @"Unknown"
#define TauUIUncountedPlaceholder @"Uncounted"



// ------------------------------------------------------------------------------------------------------------ //



typedef NS_ENUM ( NSInteger, TauContentViewTag )
    { TauSearchContentViewTag  = 0
    , TauExploreContentViewTag = 1
    , TauPlayerContentViewTag  = 2

    , TauUnknownContentViewTag = -1
    };

typedef NS_ENUM( NSInteger, TauExploreSubTabTag )
    { TauExploreSubTabMeTubeTag = 0
    , TauExploreSubTabSubscriptionsTag = 1

    , TauExploreSubTabUnknownTag = -1
    };

typedef NS_ENUM ( NSInteger, TauMeTubeSubContentViewTag )
    { TauExploreLikesSubContentViewTag      = 0
    , TauExploreUploadsSubContentViewTag    = 1
    , TauExploreHistorySubContentViewTag    = 2
    , TauExploreWatchLaterSubContentViewTag = 3
    };

typedef NS_ENUM ( NSUInteger, TauYouTubeContentType )
    { TauYouTubeVideo           = 1
    , TauYouTubeChannel         = 2
    , TauYouTubePlayList        = 3

    , TauYouTubeUnknownContent  = 0
    };

typedef NS_ENUM ( NSUInteger, TauAPIServiceConsumptionType )
    { TauAPIServiceConsumptionSearchResultsType = 1
    , TauAPIServiceConsumptionChannelsType      = 2
    , TauAPIServiceConsumptionPlaylistsType     = 3
    , TauAPIServiceConsumptionPlaylistItemsType = 4
    , TauAPIServiceConsumptionSubscriptionsType = 5

    , TauAPIServiceConsumptionUnknownType       = 0
    };

#define TAU_APP_MIN_WIDTH  500.f
#define TAU_APP_MIN_HEIGHT ( TAU_APP_MIN_WIDTH * ( 9.f / 16.f ) )

#define TAU_PAGEER_PREV 0
#define TAU_PAGEER_NEXT 1



// ------------------------------------------------------------------------------------------------------------ //



#define TAU_CLANG_DIAGNOSTIC_PUSH _Pragma( "clang diagnostic push" )
#define TAU_CLANG_DIAGNOSTIC_POP _Pragma( "clang diagnostic pop" )

// To suppress the "PerformSelector may cause a leak because its selector is unknown" warning
#define TAU_SUPPRESS_PERFORM_SELECTOR_LEAK_WARNING_BEGIN \
    TAU_CLANG_DIAGNOSTIC_PUSH \
    _Pragma( "clang diagnostic ignored \"-Warc-performSelector-leaks\"" )
    
#define TAU_SUPPRESS_PERFORM_SELECTOR_LEAK_WARNING_COMMIT TAU_CLANG_DIAGNOSTIC_POP

// Get rid of the 'undeclared selector' warning
#define TAU_SUPPRESS_UNDECLARED_SELECTOR_WARNING_BEGIN \
    TAU_CLANG_DIAGNOSTIC_PUSH \
    _Pragma( "clang diagnostic ignored \"-Wundeclared-selector\"" )

#define TAU_SUPPRESS_UNDECLARED_SELECTOR_WARNING_COMMIT TAU_CLANG_DIAGNOSTIC_POP

// Get rid of the 'undeclared selector' warning
#define TAU_FATAL_UNDECLARED_SELECTOR_WARNING_BEGIN \
    TAU_CLANG_DIAGNOSTIC_PUSH \
    _Pragma( "clang diagnostic fatal \"-Wundeclared-selector\"" )

#define TAU_FATAL_UNDECLARED_SELECTOR_WARNING_COMMIT TAU_CLANG_DIAGNOSTIC_POP



// ------------------------------------------------------------------------------------------------------------ //



// Notification Names
NSString extern* const TauShouldSwitch2SearchSegmentNotif;
NSString extern* const TauShouldSwitch2MeTubeSegmentNotif;
NSString extern* const TauShouldSwitch2PlayerSegmentNotif;

NSString extern* const TauShouldPlayVideoNotif;

NSString extern* const TauShouldExposeContentCollectionItemNotif;

// User Info Keys
NSString extern* const kGTLObject;
NSString extern* const kRequester;



// ------------------------------------------------------------------------------------------------------------ //



// General Error domains
NSString extern* const TauGeneralErrorDomain;

typedef NS_ENUM ( NSInteger, TauGeneralErrorCode )
    { TauGeneralUnknownError = -1
    , TauGeneralInvalidArgument = -1000
    };

// Error domains that is specific to central data service mechanism
NSString extern* const TauCentralDataServiceErrorDomain;

// Error domains that is specific to the pure C API of SQLite v3
NSString extern* const TauSQLiteV3ErrorDomain;

typedef NS_ENUM ( NSInteger, TauCentralDataServiceErrorCode )
    { TauCentralDataServiceUnknownError = -1

    // Specific to Tau API Service (TAS)
    , TauCentralDataServiceInvalidCredentialError   = -1000
    , TauCentralDataServiceInvalidOrConflictingOperationsCombination = -1001

    // Specific to Tau Media Service (TMS)
    , TauCentralDataServiceInvalidImageURL = -1002

    // Specific to Tau Archive Service (TVS)
    , TauCentralDataServiceSQLiteError = -1003
    };

NSString extern* const TauUnderlyingErrorDomain;

typedef NS_ENUM ( NSInteger, TauUnderlyingErrorCode )
    { TauUnderlyingUnknownError = -1
    , TauUnderlyingGTLError = -1000
    };



// ------------------------------------------------------------------------------------------------------------ //



typedef NS_ENUM ( NSInteger, TauAppMenuItemTag )
    { TauAppMenuItem       = 0
    , TauAppFileMenuItem   = 1
    , TauAppEditMenuItem   = 2
    , TauAppEditFormatItem = 3
    , TauAppViewMenuItem   = 4
    , TauAppWindowMenuItem = 5
    , TauAppHelpMenuItem   = 6
    };

#define TauAppViewSubMenuItemTag2TauContentViewTag( _Tag ) \
( _Tag - 1000 )

#define TauAppViewSubMenuItemTagFromTauContentViewTag( _Tag ) \
( ( _Tag != TauUnknownContentViewTag ) ? ( _Tag + 1000 ) : TauAppViewSubMenuUnknownItemTag )

typedef NS_ENUM ( NSInteger, TauAppViewSubMenuItemTag )
    { TauAppViewSubMenuSearchItemTag  = TauSearchContentViewTag + 1000
    , TauAppViewSubMenuExploreItemTag = TauExploreContentViewTag + 1000
    , TauAppViewSubMenuPlayerItemTag  = TauPlayerContentViewTag + 1000

    , TauAppViewSubMenuUnknownItemTag = -1
    };

#endif /* TauConstants_h */