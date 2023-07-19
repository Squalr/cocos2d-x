/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "platform/CCDevice.h"
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <string>
#include "base/ccTypes.h"
#include "platform/mac/CCDevice-apple.h"

NS_CC_BEGIN

static NSAttributedString* __attributedStringWithFontSize(NSMutableAttributedString* attributedString, CGFloat fontSize)
{
    {
        [attributedString beginEditing];
        
        [attributedString enumerateAttribute:NSFontAttributeName inRange:NSMakeRange(0, attributedString.length) options:0 usingBlock:^(id value, NSRange range, BOOL *stop) {
            
            NSFont* font = value;
            font = [[NSFontManager sharedFontManager] convertFont:font toSize:fontSize];
            
            [attributedString removeAttribute:NSFontAttributeName range:range];
            [attributedString addAttribute:NSFontAttributeName value:font range:range];
        }];
        
        [attributedString endEditing];
    }
    
    return [[attributedString copy] autorelease];
}

int Device::getDPI()
{
    NSScreen *screen = [NSScreen mainScreen];
    NSDictionary *description = [screen deviceDescription];
    NSSize displayPixelSize = [[description objectForKey:NSDeviceSize] sizeValue];
    CGSize displayPhysicalSize = CGDisplayScreenSize([[description objectForKey:@"NSScreenNumber"] unsignedIntValue]);
    
    return ((displayPixelSize.width / displayPhysicalSize.width) * 25.4f);
}

void Device::setAccelerometerEnabled(bool isEnabled)
{

}

void Device::setAccelerometerInterval(float interval)
{

}

typedef struct
{
    int height;
    int width;
    bool hasAlpha;
    bool isPremultipliedAlpha;
    unsigned char* data;
} tImageInfo;

static NSSize _calculateStringSize(NSAttributedString *str, id font, CGSize *constrainSize, bool enableWrap, int overflow)
{
    NSSize textRect = NSZeroSize;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
    : CGFLOAT_MAX;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
    : CGFLOAT_MAX;
    
    if (overflow == 1) {
        if (!enableWrap) {
            textRect.width = CGFLOAT_MAX;
            textRect.height = CGFLOAT_MAX;
        } else {
            textRect.height = CGFLOAT_MAX;
        }
    }
    
    NSSize dim;
#ifdef __MAC_10_11
    #if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) context:nil].size;
    #else
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
    #endif
#else
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
    
    
    dim.width = ceilf(dim.width);
    dim.height = ceilf(dim.height);

    return dim;
}

static NSSize _calculateRealSizeForString(NSAttributedString **str, id font, NSSize constrainSize, bool enableWrap)
{
    CGRect actualSize = CGRectMake(0, 0, constrainSize.width + 1, constrainSize.height + 1);
    int fontSize = [font pointSize];
    fontSize = fontSize + 1;

    if (!enableWrap) {
        while (actualSize.size.width > constrainSize.width ||
               actualSize.size.height > constrainSize.height) {
            fontSize = fontSize - 1;
            if (fontSize < 0) {
                actualSize = CGRectMake(0, 0, 0, 0);
                break;
            }
            
            NSMutableAttributedString *mutableString = [[*str mutableCopy] autorelease];
            *str = __attributedStringWithFontSize(mutableString, fontSize);

#ifdef __MAC_10_11
    #if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
            CGSize fitSize = [*str boundingRectWithSize:CGSizeMake( CGFLOAT_MAX, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin context:nil].size;
    #else
            CGSize fitSize = [*str boundingRectWithSize:CGSizeMake( CGFLOAT_MAX, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin].size;
    #endif
#else
            CGSize fitSize = [*str boundingRectWithSize:CGSizeMake( CGFLOAT_MAX, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin].size;
#endif

            if(fitSize.width == 0 || fitSize.height == 0) continue;
            actualSize.size = fitSize;

            if (constrainSize.width <= 0) {
                constrainSize.width = fitSize.width;
            }
            if (constrainSize.height <= 0){
                constrainSize.height = fitSize.height;
            }
            if(fontSize <= 0){
                break;
            }
        }

    }
    else {
        while (actualSize.size.height > constrainSize.height
               ||actualSize.size.width > constrainSize.width) {
            fontSize = fontSize - 1;
            if (fontSize < 0) {
                actualSize = CGRectMake(0, 0, 0, 0);
                break;
            }
            
            NSMutableAttributedString *mutableString = [[*str mutableCopy] autorelease];
            *str = __attributedStringWithFontSize(mutableString, fontSize);

#ifdef __MAC_10_11
    #if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
            CGSize fitSize = [*str boundingRectWithSize:CGSizeMake( constrainSize.width, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin context:nil].size;
    #else
            CGSize fitSize = [*str boundingRectWithSize:CGSizeMake( constrainSize.width, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin].size;
    #endif
#else
            CGSize fitSize = [*str boundingRectWithSize:CGSizeMake( constrainSize.width, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin].size;
#endif
            
            if(fitSize.width == 0 || fitSize.height == 0) continue;
            actualSize.size = fitSize;
            
            if (constrainSize.width <= 0) {
                constrainSize.width = fitSize.width;
            }
            if (constrainSize.height <= 0){
                constrainSize.height = fitSize.height;
            }
            if(fontSize <= 0){
                break;
            }
        }

    }
    return CGSizeMake(actualSize.size.width, actualSize.size.height);
}

static NSFont* _createSystemFont(const char* fontName, int size)
{
    NSString * fntName = [NSString stringWithUTF8String:fontName];
    fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
    
    // font
    NSFont *font = [NSFont fontWithName:fntName size:size];
    
    if (font == nil) {
        font = [NSFont systemFontOfSize:size];
    }
    return font;
}

void Device::setKeepScreenOn(bool value)
{
}

void Device::vibrate(float duration)
{
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC
