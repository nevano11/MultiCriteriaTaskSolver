using MultiCriteriaLibraryApi.MathModelComponents.Components;

namespace IntegrationTest;

public class MathModelComponentTests
{
    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void CriteriaInteractionWithDllTest()
    {
        string criteriaName = "criteria name";
        Criteria criteria = new Criteria(1, criteriaName, CriteriaType.MINIMIZATION);
        Assert.True(
            criteria.Id == 1 && 
            criteria.Name.Equals(criteriaName) && 
            criteria.Type.Equals(CriteriaType.MINIMIZATION));
    }
    
    [Test]
    public void AlternativeInteractionWithDllTest()
    {
        string name = "alternative name";
        var marks = new double[] { 1, 2, 3 };
        EstimateVector estimateVector = new EstimateVector(1, name, marks, 3);
        Assert.True(
            estimateVector.Id == 1 && 
            estimateVector.Name.Equals(name) && 
            estimateVector.CriteriaCount == 3 && 
            marks.SequenceEqual(estimateVector.Marks));
    }
}