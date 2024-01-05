using MultiCriteriaLibraryApi.DecisionMakingMethod.DecisionMakerInfo;
using Web.UI.Entity.Inner;

namespace Web.UI.Service;

public class DecisionMakerInfoFactory
{
    public static IDecisionMakerInfo CreateDecisionMakerInfo(DecisionMakerInfo innerMakerInfo)
    {
        if (innerMakerInfo.Parameters.TryGetValue("cedeValue", out string cedeValue))
            return new CedeValueInfo(Double.Parse(cedeValue));
        return null;
    }
}