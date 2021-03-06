#ifndef OBJECTBASE
#define OBJECTBASE

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/WriteReadTools.h"
//#include "Core/Tools/Random.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Games/GameType.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


#include <Core/Lambdas/Lambda.h>

namespace CloudberryKingdom
{
	
	struct ObjectBase : public boost::enable_shared_from_this<ObjectBase>
	{

		virtual ~ObjectBase()
		{
#ifdef BOOST_BIN
			OnDestructor( "ObjectBase" );
#endif
		}

	
		const boost::shared_ptr<GameData> &getGame() const;
		const boost::shared_ptr<Level> &getMyLevel() const;
		const boost::shared_ptr<Camera> &getCam() const;
		const boost::shared_ptr<Rand> &getRnd() const;

		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );

	
		boost::shared_ptr<ObjectData> CoreData;
	
		const boost::shared_ptr<ObjectData> &getCore() const;
		const boost::shared_ptr<TileSetInfo> getInfo() const;

		ObjectBase();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		virtual void Release();

		void SetParentBlock( const boost::shared_ptr<BlockBase> &block );

		virtual void CollectSelf();

		void StampAsUsed( int CurPhsxStep );

		virtual void MakeNew();
		virtual void PhsxStep();
		virtual void PhsxStep2();
		virtual void Draw();
		virtual void TextDraw();
		virtual void Reset( bool BoxesOnly );
		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
		virtual void Read( const boost::shared_ptr<BinaryReader> &reader );
		virtual void Write( const boost::shared_ptr<BinaryWriter> &writer );
		virtual void Interact( const boost::shared_ptr<Bob> &bob );
		virtual void Move( Vector2 shift );

		virtual void OnUsed();
		virtual void OnMarkedForDeletion();
		virtual void OnAttachedToBlock();
		virtual bool PermissionToUse();

		virtual void Smash( const boost::shared_ptr<Bob> &bob );
		virtual bool PreDecision( const boost::shared_ptr<Bob> &bob );
	};

	struct GenerationData
	{
	
		GenerationData();

		enum OverlapPreference
		{
			OverlapPreference_REMOVE_LOWER_THAN_ME,
			OverlapPreference_REMOVE_HIGHER_THAN_ME,
			OverlapPreference_REMOVE_RANDOM
		};
		/// <summary>
		/// Prevents an obstacle from being deleted if it is unused, including in object cleanup phase due to crowding.
		/// </summary>
	
		bool KeepIfUnused;

		/// <summary>
		/// If true, object will be removed if it's outside the level generator's bounds.
		/// </summary>
		bool EnforceBounds;

		bool AlwaysUse, AlwaysLandOn, AlwaysLandOn_Reluctantly;
		bool Used, RemoveIfUnused, RemoveIfUsed, RemoveIfOverlap;
		int UsedTimeStamp;

		OverlapPreference MyOverlapPreference;

		void Decide_RemoveIfUnused( float ChanceToKeep, const boost::shared_ptr<Rand> &Rnd );

		/// <summary>
		/// Removes the object if it overlaps with a block. Defaults to false.
		/// </summary>
		bool NoBlockOverlap;
		float OverlapWidth;

		/// <summary>
		/// For all objects with this set to true, a cleanup is performed with a uniform minimum distance enforced
		/// </summary>
		bool LimitGeneralDensity;

		/// <summary>
		/// For all objects of the same type with this set to true, a cleanup is performed with some minimum distance enforced
		/// </summary>
		bool LimitDensity;

		/// <summary>
		/// If true when this object is used it deletes similar surrounding objects. Implemented for NormalBlocks only.
		/// </summary>
		bool DeleteSurroundingOnUse;

		bool EdgeJumpOnly;

		/// <summary>
		/// When true the computer will not choose to land on this block.
		/// </summary>
		bool TemporaryNoLandZone;

		/// <summary>
		/// When true the computer will ALWAYS jump off this block immediately.
		/// </summary>
		bool JumpNow;

		/// <summary>
		/// How close to the edge the computer is allowed to land on this block and still use it.
		/// </summary>
		float EdgeSafety;

		bool NoBottomShift;
		bool NoMakingTopOnly;

		boost::shared_ptr<Lambda> OnUsed, OnMarkedForDeletion;
		void __StampAsUsed( int Step );

		void Release();

		void Init();
	};

	struct ObjectData
	{

		virtual ~ObjectData()
		{
#ifdef BOOST_BIN
			OnDestructor( "ObjectData" );
#endif
		}

	
		static void InitializeStatics();

	
		struct AssociatedObjData
		{
		
			unsigned long long Guid;
			bool DeleteWhenDeleted, UseWhenUsed;

			void Zero();
		};

	
		const boost::shared_ptr<Recycler> getRecycle() const;

		/// <summary>
		/// Whether this object belongs to a level in the middle of level generation
		/// </summary>
		bool LevelGenRunning();

		/// <summary>
		/// True when the object skipped its phsx update, usually due to being off screen.
		/// </summary>
		bool SkippedPhsx;

		/// <summary>
		/// True when the object has been inactive and needs to perform additional actions before normal activity resumes.
		/// </summary>
		bool WakeUpRequirements;

	
		boost::shared_ptr<TileSet> _TileSet;
	
		const boost::shared_ptr<TileSet> &getMyTileSet() const;
		void setMyTileSet( const boost::shared_ptr<TileSet> &value );

		/// <summary>
		/// Whether the object should be drawn encased in glass.
		/// </summary>
		bool Encased;

		boost::shared_ptr<AutoGen_Parameters> GetParams( const boost::shared_ptr<AutoGen> &singleton );

		std::wstring EditorCode1, EditorCode2, EditorCode3;

		bool Held, Placed;
		Vector2 HeldOffset;

		bool Holdable, EditHoldable;

		int Tag; // Used for selectively scrolling out different blocks
		static unsigned long long NextId;
		unsigned long long MyGuid;
		static unsigned long long GetId();

		int DebugCode;

		ObjectType MyType;
		bool BoxesOnly, Show, AlwaysBoxesOnly;

		bool VisualResettedOnce;

		bool RemoveOnReset, MarkedForDeletion;
		bool Active;
		//public bool _Active;
		//public bool Active
		//{
		//    get { return _Active; }
		//    set
		//    {
		//        _Active = value;
		//        if (this == "BossCenter" && value) Tools::Break();
		//    }
		//}


		/// <summary>
		/// If true the object has been set to be collected during the level generation process,
		/// the deletion was caused by the level gen algorithm deciding this object should be removed.
		/// </summary>
		bool DeletedByBob;

		/// <summary>
		/// Whether the objects OnMarkedForDeletion code has been ran or not.
		/// Used to prevent re-running the code.
		/// </summary>
		bool OnDeletionCodeRan;

		/// <summary>
		/// If the object is attached to a parent object and this flag is set to true,
		/// then the object is drawn independetly of the parent object.
		/// </summary>
		bool DoNotDrawWithParent;

		/// <summary>
		/// Whether the object should interact with the characters.
		/// </summary>
		bool Real;


		/// <summary>
		/// Whether the object is owned by a game.
		/// If False usually it is owned by a level.
		/// GameObjects are drawn by the level, but their physics is handled by the Game.
		/// </summary>
		bool IsGameObject;

		/// <summary>
		/// Does not make a clone of the object on reset, instead just calling Reset()
		/// </summary>
		bool ResetOnlyOnReset;

		int DrawLayer2, DrawLayer3;

		boost::shared_ptr<Level> MyLevel;
		int DrawLayer, DrawSubLayer;

		/// <summary>
		/// Prevents the DrawSubLayer from being overridden by it's actual position in the DrawLayer array.
		/// </summary>
		bool FixSubLayer;

		/// <summary>
		/// If true then this obstacle can be continuously scaled up and down in difficulty.
		/// </summary>
		bool ContinuousEnabled;

		PhsxData Data, StartData;

		/// <summary>
		/// The frame that the object was added on.
		/// </summary>
		int AddedTimeStamp;

		GenerationData GenData;

		std::vector<AssociatedObjData> Associations;
		unsigned long long ParentObjId;
		boost::shared_ptr<ObjectBase> ParentObject;
		boost::shared_ptr<BlockBase> ParentBlock;
		Vector2 ParentOffset;

		/// <summary>
		/// If the object just interacted with a player, this should point to the player's Bob
		/// </summary>
		const boost::shared_ptr<Bob> &getInteractingBob() const;
		void setInteractingBob( const boost::shared_ptr<Bob> &value );
		boost::shared_ptr<Bob> _InteractingBob;

		/// <summary>
		/// If the object just interacted with a player, this should point to the player
		/// </summary>
		boost::shared_ptr<PlayerData> InteractingPlayer;

		bool DoNotScrollOut;

		int StepOffset; // When an object from one level is added to another, an offset is calculated to keep it synchronized

//ORIGINAL LINE: public static void AddAssociation(bool DeleteWhenDeleted, bool UseWhenUsed, params ObjectBase[] objs)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static void AddAssociation( bool DeleteWhenDeleted, bool UseWhenUsed, ... );

		void AddAssociate( const boost::shared_ptr<ObjectBase> &obj, bool DeleteWhenDeleted, bool UseWhenUsed );

		bool IsAssociatedWith( const boost::shared_ptr<ObjectBase> &obj );

		int GetAssociatedIndex( const boost::shared_ptr<ObjectBase> &obj );

		AssociatedObjData GetAssociationData( const boost::shared_ptr<ObjectBase> &obj );

		bool Released;
		virtual void Release();

		void SetParentObj( const boost::shared_ptr<ObjectBase> &obj );

		void SetParentBlock( const boost::shared_ptr<BlockBase> &block );

		Vector2 GetPosFromParentOffset();

		void PosFromParentOffset();

		int GetPhsxStep();

		float GetIndependentPhsxStep();

		const float &getIndependentDeltaT() const;

		bool ContainsCode( const std::wstring &code );

		//bool operator == ( const std::wstring &str );
		//bool operator != ( const std::wstring &str );

		bool IsCalled ( const std::wstring &str );

		virtual void Init();

		virtual void Clone( const boost::shared_ptr<ObjectData> &A );

		virtual void Write( const boost::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const boost::shared_ptr<BinaryReader> &reader );

	
		void InitializeInstanceFields();


		ObjectData()
		{
			InitializeInstanceFields();
		}
	};

}


#endif	//#ifndef OBJECTBASE
