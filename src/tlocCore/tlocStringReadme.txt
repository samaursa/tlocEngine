//////////////////////////////////////////////////////////////////////////
/*
 * >> INTRODUCTION
 * The string class, similar to the containers, is heavily influenced by EASTL.
 * As of writing the introduction, many functions are comparable directly to
 * EASTL which may change as time goes by. This class was made first and foremost
 * for educating my on building a string class; so it is not a copy/paste of
 * EASTL. Second purpose, of course, is to use it in the 2LoC engine.
 *
 * >> NOTES
 *
 * |Exception Safety|
 *
 * The string class in this engine does not use exception safety. There is heavy
 * use of assertions (and the user is given fine grained control over them). I
 * will avoid the argument of whether exception safety slows down your program
 * or not. In general, turning it off in game engines is the norm in the industry.
 *
 * |Memory Leaks|
 *
 * The string class in this engine is not meant to be polymorphic. There is no
 * virtual destructor and therefore, 'new'ing a string object may result in a
 * memory leak.
 */
//////////////////////////////////////////////////////////////////////////