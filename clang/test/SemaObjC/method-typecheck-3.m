// RUN: %clang_cc1 -fsyntax-only -verify %s

@interface A
- (id)obj; // expected-note {{previous definition is here}}
- (A*)a; // expected-note {{previous definition is here}}
- (void)takesA: (A*)a; // expected-note {{previous definition is here}}
- (void)takesId: (id)a; // expected-note {{previous definition is here}}
@end


@interface B : A
@end

@implementation B
- (B*)obj {return self;} // expected-warning {{conflicting return type in implementation of 'obj'}}
- (B*)a { return self;}  // expected-warning {{conflicting return type in implementation of 'a'}}
- (void)takesA: (B*)a  // expected-warning {{conflicting parameter types in implementation of 'takesA:'}}
{}
- (void)takesId: (B*)a // expected-warning {{conflicting parameter types in implementation of 'takesId:'}}
{}
@end
