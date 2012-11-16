﻿#ifndef IBOUNDED
#define IBOUNDED

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	/// <summary>
	/// Interface for specifying the physical extent of an object
	/// <\summary>
	class IBound
	{
		/// <summary>
		/// Returns the TR bound
		/// </summary>
		/// <returns></returns>
	public:
		virtual Vector2 TR_Bound() = 0;

		/// <summary>
		/// Returns the BL bound
		/// </summary>
		/// <returns></returns>
		virtual Vector2 BL_Bound() = 0;

		/// <summary>
		/// Moves the object to a position presumed to be within bounds
		/// </summary>
		/// <param name="pos">The amount to shift the current position</param>
		virtual void MoveToBounded( Vector2 shift ) = 0;
	};
}


#endif	//#ifndef IBOUNDED