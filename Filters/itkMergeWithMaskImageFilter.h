#ifndef __itkMergeWithMaskImageFilter_h
#define __itkMergeWithMaskImageFilter_h
 
#include "itkImageToImageFilter.h"
 
namespace itk
{
template< typename TImage, typename TMask>
class MergeWithMaskImageFilter : public ImageToImageFilter< TImage, TImage >
{
public:
  /** Standard class typedefs. */
  typedef MergeWithMaskImageFilter             Self;
  typedef ImageToImageFilter< TImage, TImage > Superclass;
  typedef SmartPointer< Self >        Pointer;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(MergeWithMaskImageFilter, ImageToImageFilter);
 
  /** The image to be inpainted in regions where the mask is white.*/
  void SetInputImage1(const TImage* image);

  /** The image to be inpainted in regions where the mask is white.*/
  void SetInputImage2(const TImage* image);
 
  /** The mask to be inpainted. White pixels will be inpainted, black pixels will be passed through to the output.*/
  void SetInputMask(const TMask* mask);
 
protected:
  MergeWithMaskImageFilter();
  ~MergeWithMaskImageFilter(){}
 
  typename TImage::ConstPointer GetInputImage1();
  typename TImage::ConstPointer GetInputImage2();
  typename TMask::ConstPointer GetInputMask();
 
  /** Does the real work. */
  virtual void GenerateData();
 
private:
  MergeWithMaskImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
 
};
} //namespace ITK
 
 
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMergeWithMaskImageFilter.hxx"
#endif
 
 
#endif // __itkMergeWithMaskImageFilter_h
