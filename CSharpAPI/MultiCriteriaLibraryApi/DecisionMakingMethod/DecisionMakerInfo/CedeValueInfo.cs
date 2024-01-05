using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using MultiCriteriaLibraryApi.DecisionMakingMethod.DecisionMakerInfo;

public class CedeValueInfo : IDecisionMakerInfo
{
    internal IntPtr _makerInfo;
    
    public double CedeValue => CedeValueInfo_getCedeValue(_makerInfo);

    public CedeValueInfo(double cedeValue) =>
        _makerInfo = CedeValueInfo_new(cedeValue);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CedeValueInfo_new(double cedeValue);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern double CedeValueInfo_getCedeValue(IntPtr obj);

    IntPtr IDecisionMakerInfo.GetPtr()
    {
        return _makerInfo;
    }
}