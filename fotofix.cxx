#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "itkWindowedMinimumImageFilter.h"
#include "itkWindowedMaximumImageFilter.h"
#include "itkPixelWiseDistanceImageFilter.h"
#include "itkMomentsThresholdImageFilter.h"
#include "itkMergeWithMaskImageFilter.h"
#include "itkRGBPixel.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char** argv )
{

typedef itk::RGBPixel<unsigned char> RGBPixelType;
typedef itk::Image<RGBPixelType, 2> RGBImageType;
typedef itk::Image<unsigned char, 2> UCharImageType;

typedef itk::ImageFileReader<RGBImageType> ReaderType;
ReaderType::Pointer reader = ReaderType::New( );

reader->SetFileName( argv[1] );
reader->Update( );

typedef itk::SmoothingRecursiveGaussianImageFilter<RGBImageType, RGBImageType> SmoothFilterType;
SmoothFilterType::Pointer smoothingFilter = SmoothFilterType::New( );
smoothingFilter->SetSigma( 1 );
smoothingFilter->SetInput( reader->GetOutput( ));

typedef itk::WindowedMinimumImageFilter<RGBImageType,RGBImageType> MinFilterType;
MinFilterType::Pointer minFilter = MinFilterType::New( );
minFilter->SetInput( smoothingFilter->GetOutput());
minFilter->SetRadius( 5 );

typedef itk::WindowedMaximumImageFilter<RGBImageType,RGBImageType> MaxFilterType;
MaxFilterType::Pointer maxFilter = MaxFilterType::New( );
maxFilter->SetInput( minFilter->GetOutput());
maxFilter->SetRadius( 5 );

typedef itk::PixelWiseDistanceImageFilter<RGBImageType,RGBImageType,UCharImageType> DiffFilterType;
DiffFilterType::Pointer diffFilter = DiffFilterType::New( );
diffFilter->SetInput1( maxFilter->GetOutput() );
diffFilter->SetInput2( smoothingFilter->GetOutput() );

typedef itk::MomentsThresholdImageFilter<UCharImageType,UCharImageType> ThresholdFilterType;
ThresholdFilterType::Pointer thresholdFilter = ThresholdFilterType::New( );
thresholdFilter->SetInput( diffFilter->GetOutput( ));
thresholdFilter->SetInsideValue( 255 );

//typedef itk::RenyiEntropyThresholdImageFilter<UCharImageType,UCharImageType> ThresholdFilterType;
//ThresholdFilterType::Pointer thresholdFilter = ThresholdFilterType::New( );
//thresholdFilter->SetInput( diffFilter->GetOutput( ));
//thresholdFilter->SetInsideValue( 255 );

typedef itk::MergeWithMaskImageFilter<RGBImageType, UCharImageType> MergeFilterType;
MergeFilterType::Pointer mergeFilter = MergeFilterType::New( );
mergeFilter->SetInputImage1( reader->GetOutput( ) );
mergeFilter->SetInputImage2( maxFilter->GetOutput( ));
mergeFilter->SetInputMask( thresholdFilter->GetOutput( ));

typedef itk::ImageFileWriter<RGBImageType> WriterType;
WriterType::Pointer writer = WriterType::New( );
writer->SetInput( mergeFilter->GetOutput( ));
writer->SetFileName( argv[2] );
writer->Write( );

return( 1 );
}
