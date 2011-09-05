//////////////////////////////////////////////////////////////////////////
/*
 * >> INTRODUCTION
 *
 * These classes are heavily influenced by EASTL. As of writing the introduction,
 * many functions are comparable directly to EASTL which may change as time goes
 * by. These classes were made first and foremost for educating me on building
 * generic containers; so it is not a copy/paste of EASTL. Second purpose, of
 * course, is to use it in the 2LoC engine.
 *
 * >> NOTES
 *
 * |Exception Safety|
 *
 * The containers in this engine do not use exception safety. There is heavy
 * use of assertions (and the user is given control over them). I will avoid
 * the argument of whether exception safety slows down your program or not. In
 * general turning it off in game engines is the norm in the industry.
 *
 * |Memory Leaks|
 *
 * The containers in this engine are not meant to be polymorphic. They
 * are inherited whenever it made sense (to me). There is no virtual
 * destructor in any of the containers or their bases and thus 'new'ing
 * a container may result in a memory leak.
 */
//////////////////////////////////////////////////////////////////////////