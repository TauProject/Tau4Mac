//
//  TauYTDataService.h
//  Tau4Mac
//
//  Created by Tong G. on 3/16/16.
//  Copyright © 2016 Tong Kuo. All rights reserved.
//

@class TauYTDataServiceCredential;

@protocol TauYTDataServiceConsumer;

NSString extern* const TauYTDataServiceDataActionType;
    NSString extern* const TauYTDataServiceDataListSearchResultsAction;
    NSString extern* const TauYTDataServiceDataListChannelsAction;
    NSString extern* const TauYTDataServiceDataListPlaylistsAction;
    NSString extern* const TauYTDataServiceDataListPlaylistItemsAction;

NSString extern* const TauYTDataServiceDataActionMaxResultsPerPage;
NSString extern* const TauYTDataServiceDataActionPageToken;

NSString extern* const TauYTDataServiceDataActionRequirements;
    NSString extern* const TauYTDataServiceDataActionRequirementQ;
    NSString extern* const TauYTDataServiceDataActionRequirementID;
    NSString extern* const TauYTDataServiceDataActionRequirementChannelID;
    NSString extern* const TauYTDataServiceDataActionRequirementPlaylistID;
    NSString extern* const TauYTDataServiceDataActionRequirementMine;

// TauYTDataService class
@interface TauYTDataService : NSObject

#pragma mark - Core

@property ( strong, readonly ) GTLServiceYouTube* ytService;

@property ( strong, readonly ) NSString* signedInUsername;
@property ( assign, readonly ) BOOL isSignedIn;

#pragma mark - Consumers

- ( TauYTDataServiceCredential* ) registerConsumer: ( id <TauYTDataServiceConsumer> )_Consumer withMethodSignature: ( NSMethodSignature* )_Sig consumptionType: ( TauYTDataServiceConsumptionType )_ConsumptionType;
- ( void ) unregisterConsumer: ( id <TauYTDataServiceConsumer> )_Consumer withCredential: ( TauYTDataServiceCredential* )_Credential;

- ( void ) executeConsumerOperations: ( NSDictionary* )_OperationsDict
                      withCredential: ( TauYTDataServiceCredential* )_Credential
                             failure: ( void (^)( NSError* _Error ) )_FailureHandler;

#pragma mark - Singleton Instance

+ ( instancetype ) sharedService;

@end // TauYTDataService class

@protocol TauYTDataServiceConsumer <NSObject>
@end