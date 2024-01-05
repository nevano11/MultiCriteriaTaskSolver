using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.MathModelComponents.Components;

namespace MultiCriteriaLibraryApi.DecisionMakingMethod.IntermediateMethodData;

using MultiCriteriaLibraryApi.DecisionMakingMethod.Method;

public class SuccessiveConcessionsIntermediateData : AbstractIntermediateMethodData
{
    internal IntPtr _method;

    public Criteria Criteria => new Criteria(SuccessiveConcessionsIntermediateData_getCriteria(_method));

    internal SuccessiveConcessionsIntermediateData(IntPtr ptr) : base(ptr)
    {
        base._method = ptr;
    }
    
    public SuccessiveConcessionsIntermediateData(Criteria criteria) =>
        SuccessiveConcessionsIntermediateData_new(criteria._criteriaPtr);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsIntermediateData_new(IntPtr criteria);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr SuccessiveConcessionsIntermediateData_getCriteria(IntPtr obj);
}