using System.Reflection;
using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations.WeightCriteriaRelations;

namespace MultiCriteriaLibraryApi.CriteriaRelation;

public static class CriteriaRelationConverter
{
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaRelationConverter_toSimple(IntPtr sourceRelationPtr);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaRelationConverter_toAll(IntPtr sourceRelationPtr);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CriteriaRelationConverter_toWeight(IntPtr sourceRelationPtr);

    private static IntPtr GetSourcePtr(ICriteriaRelation sourceRelation)
    {
        var type = sourceRelation.GetType();
        var fieldInfo = type.GetField("_relationPtr", BindingFlags.NonPublic | BindingFlags.Instance);
        var res = (IntPtr)fieldInfo.GetValue(sourceRelation);
        return res;
    }
    
    public static AllCriteriaRelation toAllCriteriaRelation(ICriteriaRelation sourceRelation)
    {
        return new AllCriteriaRelation(CriteriaRelationConverter_toAll(GetSourcePtr(sourceRelation)));
    }
    
    public static AbstractWeightCriteriaRelation toWeightCriteriaRelation(ICriteriaRelation sourceRelation)
    {
        return new SimpleRankingMethod(CriteriaRelationConverter_toWeight(GetSourcePtr(sourceRelation)));
    }

    public static SimpleCriteriaRelation toSimpleCriteriaRelation(ICriteriaRelation sourceRelation)
    {
        return new SimpleCriteriaRelation(CriteriaRelationConverter_toSimple(GetSourcePtr(sourceRelation)));
    }
}