//
//  UITableViewCell.h
//  UIKit
//
//  Copyright (c) 2005-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIColor, UILabel, UIImageView, UIButton, UITextField, UITableView, UILongPressGestureRecognizer;

// 系统预设的cell风格
typedef NS_ENUM(NSInteger, UITableViewCellStyle) {
    // 图片+标题
    UITableViewCellStyleDefault,	// Simple cell with text label and optional image view (behavior of UITableViewCell in iPhoneOS 2.x)
    // 图片+标题______________副标题
    UITableViewCellStyleValue1,		// Left aligned label on left and right aligned label on right with blue text (Used in Settings)
    //标题+副标题
    UITableViewCellStyleValue2,		// Right aligned label on left with blue text and left aligned label on right (Used in Phone/Contacts)
    // 图片+标题(上)+副标题(下)
    UITableViewCellStyleSubtitle	// Left aligned label on top and left aligned label on bottom with gray text (Used in iPod).
};             // available in iPhone OS 3.0

// 分隔线风格
typedef NS_ENUM(NSInteger, UITableViewCellSeparatorStyle) {
    // 无分隔线
    UITableViewCellSeparatorStyleNone,
    // 单实线(默认)
    UITableViewCellSeparatorStyleSingleLine,
    // 单虚线
    UITableViewCellSeparatorStyleSingleLineEtched   // This separator style is only supported for grouped style table views currently
} __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UITableViewCellSelectionStyle) {
    UITableViewCellSelectionStyleNone,
    UITableViewCellSelectionStyleBlue,
    UITableViewCellSelectionStyleGray,
    UITableViewCellSelectionStyleDefault NS_ENUM_AVAILABLE_IOS(7_0)
};

typedef NS_ENUM(NSInteger, UITableViewCellFocusStyle) {
    UITableViewCellFocusStyleDefault,
    UITableViewCellFocusStyleCustom
} NS_ENUM_AVAILABLE_IOS(9_0);

typedef NS_ENUM(NSInteger, UITableViewCellEditingStyle) {
    UITableViewCellEditingStyleNone,
    UITableViewCellEditingStyleDelete,
    UITableViewCellEditingStyleInsert
};

// 系统预设的cell附件风格
typedef NS_ENUM(NSInteger, UITableViewCellAccessoryType) {
    // 不使用
    UITableViewCellAccessoryNone,                                                      // don't show any accessory view
    //一个 > 号
    UITableViewCellAccessoryDisclosureIndicator,                                       // regular chevron. doesn't track
    //一个详情按钮 + 一个 > 号
    UITableViewCellAccessoryDetailDisclosureButton __TVOS_PROHIBITED,                 // info button w/ chevron. tracks
    // 一个 √ 号
    UITableViewCellAccessoryCheckmark,                                                 // checkmark. doesn't track
    //一个详情按钮
    UITableViewCellAccessoryDetailButton NS_ENUM_AVAILABLE_IOS(7_0)  __TVOS_PROHIBITED // info button. tracks
};

typedef NS_OPTIONS(NSUInteger, UITableViewCellStateMask) {
    UITableViewCellStateDefaultMask                     = 0,
    UITableViewCellStateShowingEditControlMask          = 1 << 0,
    UITableViewCellStateShowingDeleteConfirmationMask   = 1 << 1
};

#define UITableViewCellStateEditingMask UITableViewCellStateShowingEditControlMask

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableViewCell : UIView <NSCoding, UIGestureRecognizerDelegate>

// Designated initializer.  If the cell can be reused, you must pass in a reuse identifier.  You should use the same reuse identifier for all cells of the same form.  
- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(nullable NSString *)reuseIdentifier NS_AVAILABLE_IOS(3_0) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// Content.  These properties provide direct access to the internal label and image views used by the table view cell.  These should be used instead of the content properties below.
// 图片
@property (nonatomic, readonly, strong, nullable) UIImageView *imageView NS_AVAILABLE_IOS(3_0);   // default is nil.  image view will be created if necessary.

// 标题标签
@property (nonatomic, readonly, strong, nullable) UILabel *textLabel NS_AVAILABLE_IOS(3_0);   // default is nil.  label will be created if necessary.
// 详情标签
@property (nonatomic, readonly, strong, nullable) UILabel *detailTextLabel NS_AVAILABLE_IOS(3_0); // default is nil.  label will be created if necessary (and the current style supports a detail label).

// If you want to customize cells by simply adding additional views, you should add them to the content view so they will be positioned appropriately as the cell transitions into and out of editing mode.
@property (nonatomic, readonly, strong) UIView *contentView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'backgroundView' will be added as a subview behind all other views.
@property (nonatomic, strong, nullable) UIView *backgroundView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'selectedBackgroundView' will be added as a subview directly above the backgroundView if not nil, or behind all other views. It is added as a subview only when the cell is selected. Calling -setSelected:animated: will cause the 'selectedBackgroundView' to animate in and out with an alpha fade.
@property (nonatomic, strong, nullable) UIView *selectedBackgroundView;

// If not nil, takes the place of the selectedBackgroundView when using multiple selection.
@property (nonatomic, strong, nullable) UIView *multipleSelectionBackgroundView NS_AVAILABLE_IOS(5_0);

@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;
- (void)prepareForReuse;                                                        // if the cell is reusable (has a reuse identifier), this is called just before the cell is returned from the table view method dequeueReusableCellWithIdentifier:.  If you override, you MUST call super.

@property (nonatomic) UITableViewCellSelectionStyle   selectionStyle;             // default is UITableViewCellSelectionStyleBlue.
@property (nonatomic, getter=isSelected) BOOL         selected;                   // set selected state (title, image, background). default is NO. animated is NO
@property (nonatomic, getter=isHighlighted) BOOL      highlighted;                // set highlighted state (title, image, background). default is NO. animated is NO
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;                     // animate between regular and selected state
- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated;               // animate between regular and highlighted state

@property (nonatomic, readonly) UITableViewCellEditingStyle editingStyle;         // default is UITableViewCellEditingStyleNone. This is set by UITableView using the delegate's value for cells who customize their appearance accordingly.
@property (nonatomic) BOOL                            showsReorderControl;        // default is NO
@property (nonatomic) BOOL                            shouldIndentWhileEditing;   // default is YES.  This is unrelated to the indentation level below.

// cell附件风格.默认不使用附件
@property (nonatomic) UITableViewCellAccessoryType    accessoryType;              // default is UITableViewCellAccessoryNone. use to set standard type
// 自定义附件视图.accessoryView优先级>accessoryType
@property (nonatomic, strong, nullable) UIView       *accessoryView;              // if set, use custom view. ignore accessoryType. tracks if enabled can calls accessory action
// 编辑状态下的附件类型
@property (nonatomic) UITableViewCellAccessoryType    editingAccessoryType;       // default is UITableViewCellAccessoryNone. use to set standard type
// 编辑状态下的附件视图
@property (nonatomic, strong, nullable) UIView       *editingAccessoryView;       // if set, use custom view. ignore editingAccessoryType. tracks if enabled can calls accessory action

@property (nonatomic) NSInteger                       indentationLevel;           // adjust content indent. default is 0
@property (nonatomic) CGFloat                         indentationWidth;           // width for each level. default is 10.0
@property (nonatomic) UIEdgeInsets                    separatorInset NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED; // allows customization of the separator frame

// 设置或获取是否处于编辑状态
@property (nonatomic, getter=isEditing) BOOL          editing;                    // show appropriate edit controls (+/- & reorder). By default -setEditing: calls setEditing:animated: with NO for animated.
// 以动画的方式切换编辑状态
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

@property(nonatomic, readonly) BOOL                   showingDeleteConfirmation;  // currently showing "Delete" button

@property (nonatomic) UITableViewCellFocusStyle       focusStyle NS_AVAILABLE_IOS(9_0) UI_APPEARANCE_SELECTOR;

// These methods can be used by subclasses to animate additional changes to the cell when the cell is changing state
// Note that when the cell is swiped, the cell will be transitioned into the UITableViewCellStateShowingDeleteConfirmationMask state,
// but the UITableViewCellStateShowingEditControlMask will not be set.
- (void)willTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);
- (void)didTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);

@end

@interface UITableViewCell (UIDeprecated)

// Frame is ignored.  The size will be specified by the table view width and row height.
- (id)initWithFrame:(CGRect)frame reuseIdentifier:(nullable NSString *)reuseIdentifier NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// Content properties.  These properties were deprecated in iPhone OS 3.0.  The textLabel and imageView properties above should be used instead.
// For selected attributes, set the highlighted attributes on the textLabel and imageView.
@property (nonatomic, copy, nullable)   NSString *text NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                        // default is nil
@property (nonatomic, strong, nullable) UIFont   *font NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                        // default is nil (Use default font)
@property (nonatomic) NSTextAlignment   textAlignment NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is UITextAlignmentLeft
@property (nonatomic) NSLineBreakMode   lineBreakMode NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is UILineBreakModeTailTruncation
@property (nonatomic, strong, nullable) UIColor  *textColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                   // default is nil (text draws black)
@property (nonatomic, strong, nullable) UIColor  *selectedTextColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;           // default is nil (text draws white)

@property (nonatomic, strong, nullable) UIImage  *image NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                       // default is nil. appears on left next to title.
@property (nonatomic, strong, nullable) UIImage  *selectedImage NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is nil

// Use the new editingAccessoryType and editingAccessoryView instead
@property (nonatomic) BOOL              hidesAccessoryWhenEditing NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;   // default is YES

// Use the table view data source method -tableView:commitEditingStyle:forRowAtIndexPath: or the table view delegate method -tableView:accessoryButtonTappedForRowWithIndexPath: instead
@property (nonatomic, assign, nullable) id        target NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                      // target for insert/delete/accessory clicks. default is nil (i.e. go up responder chain). weak reference
@property (nonatomic, nullable) SEL               editAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                  // action to call on insert/delete call. set by UITableView
@property (nonatomic, nullable) SEL               accessoryAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;             // action to call on accessory view clicked. set by UITableView

@end

NS_ASSUME_NONNULL_END
