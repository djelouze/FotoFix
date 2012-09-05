#ifndef __itkMergeWithMaskImageFilter_txx
#define __itkMergeWithMaskImageFilter_txx
 
#include "itkMergeWithMaskImageFilter.h"
 
#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
 
namespace itk
{
 
template< typename TImage, typename TMask>
MergeWithMaskImageFilter<TImage, TMask>::MergeWithMaskImageFilter()
{
  this->SetNumberOfRequiredInputs(3);
}
 
template< typename TImage, typename TMask>
void MergeWithMaskImageFilter<TImage, TMask>::SetInputImage1(const TImage* image)
{
  this->SetNthInput(0, const_cast<TImage*>(image));
}

template< typename TImage, typename TMask>
void MergeWithMaskImageFilter<TImage, TMask>::SetInputImage2(const TImage* image)
{
  this->SetNthInput(1, const_cast<TImage*>(image));
}
 
template< typename TImage, typename TMask>
void MergeWithMaskImageFilter<TImage, TMask>::SetInputMask(const TMask* mask)
{
  this->SetNthInput(2, const_cast<TMask*>(mask));
}
 
template< typename TImage, typename TMask>
typename TImage::ConstPointer MergeWithMaskImageFilter<TImage, TMask>::GetInputImage1()
{
  return static_cast< const TImage * >
         ( this->ProcessObject::GetInput(0) );
}

template< typename TImage, typename TMask>
typename TImage::ConstPointer MergeWithMaskImageFilter<TImage, TMask>::GetInputImage2()
{
  return static_cast< const TImage * >
         ( this->ProcessObject::GetInput(1) );
}
 
template< typename TImage, typename TMask>
typename TMask::ConstPointer MergeWithMaskImageFilter<TImage, TMask>::GetInputMask()
{
  return static_cast< const TMask * >
         ( this->ProcessObject::GetInput(2) );
}
 
template< typename TImage, typename TMask>
void MergeWithMaskImageFilter<TImage, TMask>::GenerateData()
{
  typename TImage::ConstPointer input1 = this->GetInputImage1();
  typename TImage::ConstPointer input2 = this->GetInputImage2();
  typename TMask::ConstPointer mask = this->GetInputMask();
 
  typename TImage::Pointer output = this->GetOutput();
  output->SetRegions(input1->GetLargestPossibleRegion());
  output->Allocate();
 
  itk::ImageRegionIterator<TImage> outputIterator(output, output->GetLargestPossibleRegion());
  itk::ImageRegionConstIterator<TImage> input1Iterator(input1, input1->GetLargestPossibleRegion());
  itk::ImageRegionConstIterator<TImage> input2Iterator(input2, input2->GetLargestPossibleRegion());
  itk::ImageRegionConstIterator<TMask> maskIterator(mask, mask->GetLargestPossibleRegion());
 
  while(!outputIterator.IsAtEnd())
    {
    if( maskIterator.Get() == 255 )
      {
      outputIterator.Set(input1Iterator.Get());
      }
    else
      {
      outputIterator.Set(input2Iterator.Get());
      }
 
    ++input1Iterator;
    ++input2Iterator;
    ++maskIterator;
    ++outputIterator;
    }
 
}
 
}// end namespace
 
 
#endif
